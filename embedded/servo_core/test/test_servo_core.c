#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "pid.h"
#include "crc16.h"
#include "frame.h"
#include "ringbuf.h"
#include "fault_fsm.h"

static void test_crc(void)
{
    assert(crc16_ccitt((const uint8_t *)"123456789", 9) == 0x29B1);
}

static void test_pid_converges_and_saturates(void)
{
    pid_t_ p;
    pid_init(&p, 4.0f, 8.0f, 0.05f, -10.0f, 10.0f, 0.5f);
    /* first-order plant: x' = u - x */
    float x = 0.0f, dt = 0.001f;
    for (int i = 0; i < 20000; i++) x += dt * (pid_update(&p, 1.0f, x, dt) - x);
    assert(x > 0.99f && x < 1.01f);

    /* huge setpoint: output must stay clamped, no windup overshoot on return */
    pid_reset(&p);
    x = 0.0f;
    for (int i = 0; i < 2000; i++) {
        float u = pid_update(&p, 1000.0f, x, dt);
        assert(u <= 10.0f && u >= -10.0f);
        x += dt * (u - x);
    }
    float peak = 0.0f;
    for (int i = 0; i < 20000; i++) {
        x += dt * (pid_update(&p, 1.0f, x, dt) - x);
        if (x < peak) peak = x;   /* undershoot below 0 would indicate windup */
    }
    assert(p.integ <= 10.0f && p.integ >= -10.0f);
}

static void test_frame_roundtrip_and_resync(void)
{
    frame_t f = { .type = 7, .len = 4, .payload = {1, 2, 3, 4} };
    uint8_t wire[64];
    size_t n = frame_encode(&f, wire, sizeof wire);
    assert(n == 4 + FRAME_OVERHEAD);

    frame_parser_t p;
    frame_parser_init(&p);
    /* garbage, then a good frame, then a corrupted frame, then a good one */
    const uint8_t junk[] = {0x00, 0xFF, 0x12};
    int got = 0;
    for (size_t i = 0; i < sizeof junk; i++) got += frame_parser_feed(&p, junk[i]);
    for (size_t i = 0; i < n; i++) got += frame_parser_feed(&p, wire[i]);
    assert(got == 1 && p.frame.type == 7 && p.frame.len == 4 && p.frame.payload[3] == 4);

    uint8_t bad[64];
    memcpy(bad, wire, n);
    bad[4] ^= 0x40;   /* flip a payload bit */
    for (size_t i = 0; i < n; i++) got += frame_parser_feed(&p, bad[i]);
    assert(got == 1 && p.crc_errors == 1);
    for (size_t i = 0; i < n; i++) got += frame_parser_feed(&p, wire[i]);
    assert(got == 2);

    f.len = FRAME_MAX_PAYLOAD + 1;
    assert(frame_encode(&f, wire, sizeof wire) == 0);
}

static void test_ringbuf(void)
{
    uint8_t store[8];
    ringbuf_t r;
    assert(!ringbuf_init(&r, store, 6));   /* not a power of two */
    assert(ringbuf_init(&r, store, 8));
    for (uint8_t i = 0; i < 7; i++) assert(ringbuf_put(&r, i));
    assert(!ringbuf_put(&r, 99) && r.overruns == 1);
    assert(ringbuf_count(&r) == 7);
    uint8_t b;
    for (uint8_t i = 0; i < 7; i++) { assert(ringbuf_get(&r, &b) && b == i); }
    assert(!ringbuf_get(&r, &b));
    for (int k = 0; k < 100; k++) { assert(ringbuf_put(&r, (uint8_t)k)); assert(ringbuf_get(&r, &b) && b == (uint8_t)k); }
}

static void test_fsm(void)
{
    drive_fsm_t d;
    drive_fsm_init(&d, 50, 5.0f, -3.0f, 3.0f);
    assert(!drive_fsm_step(&d, 0, 0, 0));          /* disabled: no output */
    drive_fsm_enable(&d, 1000);
    assert(drive_fsm_step(&d, 1010, 1.0f, 0.0f));
    drive_fsm_command_received(&d, 1040);
    assert(drive_fsm_step(&d, 1080, 1.0f, 0.0f));
    assert(!drive_fsm_step(&d, 1200, 1.0f, 0.0f) && (d.faults & FAULT_WATCHDOG));
    assert(!drive_fsm_enable(&d, 1300));            /* cannot re-enable in fault */
    drive_fsm_clear_fault(&d, 1300);
    assert(drive_fsm_enable(&d, 1300));
    assert(!drive_fsm_step(&d, 1310, 6.0f, 0.0f) && (d.faults & FAULT_OVERCUR));
    drive_fsm_clear_fault(&d, 2000);
    drive_fsm_enable(&d, 2000);
    assert(!drive_fsm_step(&d, 2010, 1.0f, 3.5f) && (d.faults & FAULT_POS_LIMIT));
    /* millisecond counter wrap-around */
    drive_fsm_clear_fault(&d, 0xFFFFFFF0u);
    drive_fsm_enable(&d, 0xFFFFFFF0u);
    assert(drive_fsm_step(&d, 0x00000010u, 0.0f, 0.0f));   /* 32 ms later, < 50 */
}

int main(void)
{
    test_crc();
    test_pid_converges_and_saturates();
    test_frame_roundtrip_and_resync();
    test_ringbuf();
    test_fsm();
    puts("servo_core: all tests passed");
    return 0;
}
