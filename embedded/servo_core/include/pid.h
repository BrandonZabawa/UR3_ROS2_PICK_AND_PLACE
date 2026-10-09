#ifndef SERVO_PID_H
#define SERVO_PID_H

/* Portable PID: no heap, no libc beyond math-free arithmetic, no globals.
 * Derivative acts on the measurement (no kick on setpoint steps) and is
 * low-pass filtered. Integrator uses conditional anti-windup. */

typedef struct {
    float kp, ki, kd;
    float out_min, out_max;
    float d_alpha;      /* derivative filter coeff in (0,1]; 1 = unfiltered */
    float integ;
    float prev_meas;
    float d_state;
    int   primed;       /* 0 until first update, avoids a derivative spike */
} pid_t_;

void  pid_init(pid_t_ *p, float kp, float ki, float kd,
               float out_min, float out_max, float d_alpha);
void  pid_reset(pid_t_ *p);
/* dt in seconds, must be > 0. Returns the clamped output. */
float pid_update(pid_t_ *p, float setpoint, float meas, float dt);

#endif
