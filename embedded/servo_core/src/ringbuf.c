#include "ringbuf.h"

int ringbuf_init(ringbuf_t *r, uint8_t *storage, size_t cap)
{
    if (cap < 2 || (cap & (cap - 1)) != 0) return 0;
    r->buf = storage;
    r->mask = cap - 1;
    r->head = r->tail = 0;
    r->overruns = 0;
    return 1;
}

int ringbuf_put(ringbuf_t *r, uint8_t b)
{
    size_t h = r->head;
    if (((h + 1) & r->mask) == r->tail) {   /* one slot kept free */
        r->overruns++;
        return 0;
    }
    r->buf[h] = b;
    r->head = (h + 1) & r->mask;
    return 1;
}

int ringbuf_get(ringbuf_t *r, uint8_t *b)
{
    size_t t = r->tail;
    if (t == r->head) return 0;
    *b = r->buf[t];
    r->tail = (t + 1) & r->mask;
    return 1;
}

size_t ringbuf_count(const ringbuf_t *r)
{
    return (r->head - r->tail) & r->mask;
}
