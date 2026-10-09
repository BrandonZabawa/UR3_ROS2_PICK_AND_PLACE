#include "pid.h"

static float clampf(float v, float lo, float hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

void pid_init(pid_t_ *p, float kp, float ki, float kd,
              float out_min, float out_max, float d_alpha)
{
    p->kp = kp; p->ki = ki; p->kd = kd;
    p->out_min = out_min; p->out_max = out_max;
    p->d_alpha = clampf(d_alpha, 0.001f, 1.0f);
    pid_reset(p);
}

void pid_reset(pid_t_ *p)
{
    p->integ = 0.0f;
    p->prev_meas = 0.0f;
    p->d_state = 0.0f;
    p->primed = 0;
}

float pid_update(pid_t_ *p, float setpoint, float meas, float dt)
{
    float err = setpoint - meas;
    float d_raw = 0.0f;

    if (dt <= 0.0f) {
        return clampf(p->kp * err + p->integ, p->out_min, p->out_max);
    }
    if (p->primed) {
        d_raw = -(meas - p->prev_meas) / dt;   /* derivative on measurement */
    }
    p->prev_meas = meas;
    p->primed = 1;
    p->d_state += p->d_alpha * (d_raw - p->d_state);

    float unsat = p->kp * err + p->integ + p->kd * p->d_state;
    float out = clampf(unsat, p->out_min, p->out_max);

    /* Conditional anti-windup: only integrate if not pushing further into
     * saturation. */
    if (out == unsat || (unsat > p->out_max && err < 0.0f) ||
        (unsat < p->out_min && err > 0.0f)) {
        p->integ += p->ki * err * dt;
        p->integ = clampf(p->integ, p->out_min, p->out_max);
    }
    return out;
}
