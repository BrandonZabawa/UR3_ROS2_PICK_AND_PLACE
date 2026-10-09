#include "fault_fsm.h"

void drive_fsm_init(drive_fsm_t *d, uint32_t watchdog_ms, float current_limit_a,
                    float pos_min, float pos_max)
{
    d->state = ST_DISABLED;
    d->faults = FAULT_NONE;
    d->last_cmd_ms = 0;
    d->watchdog_ms = watchdog_ms;
    d->current_limit_a = current_limit_a;
    d->pos_min = pos_min;
    d->pos_max = pos_max;
}

void drive_fsm_command_received(drive_fsm_t *d, uint32_t now_ms)
{
    d->last_cmd_ms = now_ms;
}

int drive_fsm_enable(drive_fsm_t *d, uint32_t now_ms)
{
    if (d->state == ST_FAULT) return 0;
    d->state = ST_ENABLED;
    d->last_cmd_ms = now_ms;   /* grace period from enable */
    return 1;
}

void drive_fsm_disable(drive_fsm_t *d)
{
    if (d->state != ST_FAULT) d->state = ST_DISABLED;
}

int drive_fsm_step(drive_fsm_t *d, uint32_t now_ms, float current_a, float pos)
{
    if (d->state != ST_ENABLED) return 0;
    /* unsigned subtraction is wrap-safe for the 32-bit ms counter */
    if ((uint32_t)(now_ms - d->last_cmd_ms) > d->watchdog_ms) d->faults |= FAULT_WATCHDOG;
    if (current_a > d->current_limit_a || current_a < -d->current_limit_a)
        d->faults |= FAULT_OVERCUR;
    if (pos < d->pos_min || pos > d->pos_max) d->faults |= FAULT_POS_LIMIT;
    if (d->faults) { d->state = ST_FAULT; return 0; }
    return 1;
}

int drive_fsm_clear_fault(drive_fsm_t *d, uint32_t now_ms)
{
    if (d->state != ST_FAULT) return 1;
    d->faults = FAULT_NONE;
    d->state = ST_DISABLED;
    d->last_cmd_ms = now_ms;
    return 1;
}
