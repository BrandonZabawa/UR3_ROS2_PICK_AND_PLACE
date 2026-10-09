# Computer-vision deliverables: plan, scope, and how to run them

> **Scope note:** the schedule and acceptance criteria in `DELIVERABLES.md` (Part A) are
> the authoritative lean version (2-4 weeks). This file is the longer technical
> reference; steps marked *optional* below are not required for the agreed deliverables.

Three class deliverables, each with one measurable claim, one script/notebook that
produces it, and one table or figure for the report. Nothing here exists in the repo
yet (verified by grep: no calibration code, no custom-trained detector, no GT pose
comparison). `ur_perception` currently uses HSV colour thresholding plus stock COCO
`yolov8n.pt`, and `DepthPoseEstimator.estimate_object_pose` returns an identity
quaternion, so it estimates 3-DoF position, not 6-DoF pose.

## Where the compute runs

| Stage | Where | Why |
|---|---|---|
| Gazebo + ROS data capture | Your laptop (headless, `use_gazebo_gui:=false`), or a free Linux VM | Needs ROS 2 + Gazebo; no GPU needed at low resolution |
| YOLO training / validation | **Google Colab (T4 GPU)** | Only step that needs a GPU. See `notebooks/yolo_train_colab.ipynb` |
| Hand-eye calibration, pose estimation, evaluation | Laptop CPU | NumPy/OpenCV/Open3D only |

The seam between laptop and Colab is a zip file in the YOLO dataset format. Nothing
in training depends on ROS.

## Deliverable 1: synthetic labelled dataset + fine-tuned YOLO (metric: mAP)

**Claim to report:** "YOLOv8n fine-tuned on N synthetic images reaches mAP@0.5 = X and
mAP@0.5:0.95 = Y on a held-out synthetic test split (and Z on a small set of
domain-shifted scenes)."

1. **Labels come from the simulator, not by hand.** Gazebo Harmonic provides a
   `boundingbox_camera` sensor and the `gz-sim-label-system` plugin (give each
   model a `<label>` integer). Add a second sensor to the head camera pointing at
   the same view as the colour camera. Check that your installed `ros_gz_bridge`
   supports the bounding-box message; if not, subscribe with `gz topic` or the
   `gz-transport` Python bindings instead of bridging.
   Fallback if the sensor is troublesome: project known object poses (from
   `/world/default/pose/info`) through the camera intrinsics and compute 2D boxes
   yourself. This is simple and also useful for deliverable 3.
2. **Domain randomisation loop** (the part that makes the dataset worth anything):
   per frame, randomise object pose, colour/texture, count, distractors, light
   direction/intensity, and small camera pose jitter. Settle physics before capture.
3. **Export** to YOLO format: `images/{train,val,test}`, `labels/*.txt`
   (`class cx cy w h`, normalised), `data.yaml`. Split **by scene seed**, not by
   frame, otherwise val leaks into train.
4. **Train + evaluate in Colab.** The notebook does `YOLO('yolov8n.pt').train(...)`
   then `.val(split='test')` and prints mAP50 / mAP50-95 / per-class AP.
5. *(Optional)* **Add one honest baseline:** the existing HSV detector scored with the same
   metric. "Fine-tuned YOLO beats the colour baseline by X mAP" is a stronger
   result than a single number.

Pitfall to state in the report: a synthetic-only test set is easy. Say so in the
limitations paragraph. A held-out lighting/texture condition is optional but strengthens the result.

## Deliverable 2: camera + hand-eye calibration

**Claim to report:** "Intrinsics recovered to within X% of the simulator's ground
truth; hand-eye transform recovered to within X mm / Y deg of ground truth;
reprojection RMS Z px."

The simulator is an advantage: the ground-truth extrinsics are in the URDF
(`camera_head_joint`), and the true intrinsics are in `/camera_head/camera_info`.
So you can *measure* calibration error, which real-hardware projects cannot.

1. Add a ChArUco or checkerboard model to the world.
2. Move the arm through ~15-25 diverse poses (rotations as well as translations;
   degenerate motions make hand-eye ill-posed). At each pose record image and
   `base_link -> tool0` from TF.
3. **Intrinsics:** `cv2.calibrateCamera` (or `cv2.aruco.calibrateCameraCharuco`).
   Compare K and distortion to `camera_info`. Note sim cameras usually have zero
   distortion, so optionally inject synthetic distortion to make the test non-trivial.
4. **Hand-eye:** `cv2.calibrateHandEye` (try TSAI, PARK, DANIILIDIS and compare).
   - Eye-in-hand: `wrist_camera:=true` is already supported by the launch file.
   - Eye-to-hand: the head camera. Use the same function with inverted robot
     poses (base-to-gripper instead of gripper-to-base).
5. Compare the result with the URDF transform; report translation (mm) and rotation
   (deg) error, and how error varies with number of poses.
6. Publish the result as a static TF so the rest of the stack consumes it.

Do not edit `camera_info` to match your result, and do not copy the URDF value into
the "calibrated" output; the point is to recover it independently.

## Deliverable 3: 6-DoF pose from depth vs ground truth

**Claim to report:** "Median translation error X mm, median rotation error Y deg,
ADD(-S) AUC Z on N frames."

1. Ground truth: `/world/<name>/pose/info` (or a Gazebo model-state query) for every
   object, transformed into the camera frame via the calibrated transform.
2. Estimate: crop the point cloud / depth with the YOLO box (links deliverable 1 to
   this one), remove the support plane (RANSAC, Open3D), then
   - **Baseline A:** centroid + PCA axes (cheap, ambiguous for symmetric objects).
   - **Baseline B:** ICP of the segment against the object's known CAD/mesh
     (`o3d.pipelines.registration`), initialised from A.
3. Metrics: translation error (mm), rotation geodesic error (deg), ADD and ADD-S
   (ADD-S for symmetric objects such as cylinders; a cylinder's yaw is
   unobservable, so scoring it with plain ADD is a mistake).
4. *(Optional)* Add depth noise (Gazebo `<noise>` on the depth sensor) and show error vs noise.
5. Replace the identity quaternion in `DepthPoseEstimator.estimate_object_pose`
   with the estimator's output so the pipeline actually uses it.

## Suggested order

See `DELIVERABLES.md` for the day-by-day 2-week and 4-week schedules. The three tracks run
in parallel after a short shared setup; calibration output feeds the pose estimator last.

## Installing RViz on Linux

The repo says Humble. Humble supports **Ubuntu 22.04 only**; Jazzy supports 24.04.
The most common reason `apt install ros-humble-rviz2` fails is a distro/OS mismatch
or a missing ROS apt source. Run these and compare with your debug log:

```bash
lsb_release -ds                          # 22.04 -> humble, 24.04 -> jazzy
echo $ROS_DISTRO
apt-cache policy ros-$ROS_DISTRO-rviz2   # "Candidate: (none)" means apt source missing
```

If the candidate is `(none)`, add the ROS 2 apt source:

```bash
sudo apt install -y software-properties-common curl
sudo add-apt-repository universe
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
  -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" \
  | sudo tee /etc/apt/sources.list.d/ros2.list
sudo apt update && sudo apt install -y ros-$ROS_DISTRO-rviz2
```

Other causes: running in WSL2 or a VM without GL (RViz installs fine but fails to
start; try `LIBGL_ALWAYS_SOFTWARE=1 rviz2`), or no `sudo apt update` after adding
the source. Paste the exact error if it is none of these.

If the laptop cannot render RViz or Gazebo at all, use the headless route
(`launch_headless.sh`, `use_rviz:=false use_gazebo_gui:=false`) and inspect results
through saved images and the existing web dashboard.
