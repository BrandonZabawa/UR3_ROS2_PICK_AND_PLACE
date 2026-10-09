#ifndef SERVO_RINGBUF_H
#define SERVO_RINGBUF_H
#include <stdint.h>
#include <stddef.h>

/* Single-producer / single-consumer byte ring (e.g. UART ISR -> main loop).
 * Capacity must be a power of two. head is written only by the producer,
 * tail only by the consumer. On a real MCU, make head/tail volatile (done
 * here) and, on cores with caches or reordering, add the target's memory
 * barrier between the data write and the index update. */
typedef struct {
    uint8_t *buf;
    size_t   mask;
    volatile size_t head;
    volatile size_t tail;
    volatile uint32_t overruns;
} ringbuf_t;

int    ringbuf_init(ringbuf_t *r, uint8_t *storage, size_t cap_pow2);
int    ringbuf_put(ringbuf_t *r, uint8_t b);   /* 1 ok, 0 full (counted) */
int    ringbuf_get(ringbuf_t *r, uint8_t *b);  /* 1 ok, 0 empty */
size_t ringbuf_count(const ringbuf_t *r);

#endif
