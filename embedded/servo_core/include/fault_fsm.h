#ifndef SERVO_FAULT_FSM_H
#define SERVO_FAULT_FSM_H
#include <stdint.h>

/* Joint-drive state machine with a command watchdog.
 * Any fault forces output to zero; leaving FAULT requires an explicit
 * clear while the fault condition is gone. Pure logic, time injected. */
typedef enum { ST_DISABLED, ST_ENABLED, ST_FAULT } drive_state_t;

typedef enum {
    FAULT_NONE      = 0,
    FAULT_WATCHDOG  = 1u << 0,   /* no valid command within timeout */
    FAULT_OVERCUR   = 1u << 1,
    FAULT_POS_LIMIT = 1u << 2
} fault_bits_t;

typedef struct {
    drive_state_t state;
    uint32_t faults;
    uint32_t last_cmd_ms;
    uint32_t watchdog_ms;
    float    current_limit_a;
    float    pos_min, pos_max;
} drive_fsm_t;

void drive_fsm_init(drive_fsm_t *d, uint32_t watchdog_ms, float current_limit_a,
                    float pos_min, float pos_max);
void drive_fsm_command_received(drive_fsm_t *d, uint32_t now_ms);
int  drive_fsm_enable(drive_fsm_t *d, uint32_t now_ms);   /* 1 if enabled */
void drive_fsm_disable(drive_fsm_t *d);
int  drive_fsm_clear_fault(drive_fsm_t *d, uint32_t now_ms); /* 1 if cleared */
/* Call every control tick. Returns 1 if output may be driven, else 0. */
int  drive_fsm_step(drive_fsm_t *d, uint32_t now_ms, float current_a, float pos);

#endif
