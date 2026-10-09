#include "frame.h"
#include "crc16.h"

size_t frame_encode(const frame_t *f, uint8_t *out, size_t out_cap)
{
    if (f->len > FRAME_MAX_PAYLOAD || out_cap < (size_t)f->len + FRAME_OVERHEAD) {
        return 0;
    }
    size_t n = 0;
    out[n++] = FRAME_SOF;
    out[n++] = f->len;
    out[n++] = f->type;
    for (uint8_t i = 0; i < f->len; i++) out[n++] = f->payload[i];
    uint16_t crc = crc16_ccitt(&out[1], (size_t)f->len + 2u);
    out[n++] = (uint8_t)(crc >> 8);
    out[n++] = (uint8_t)(crc & 0xFF);
    return n;
}

void frame_parser_init(frame_parser_t *p)
{
    p->state = RX_SOF;
    p->idx = 0;
    p->crc_hi = 0;
    p->crc_errors = 0;
    p->len_errors = 0;
    p->frame.len = 0;
    p->frame.type = 0;
}

int frame_parser_feed(frame_parser_t *p, uint8_t b)
{
    switch (p->state) {
    case RX_SOF:
        if (b == FRAME_SOF) p->state = RX_LEN;
        break;
    case RX_LEN:
        if (b > FRAME_MAX_PAYLOAD) {
            p->len_errors++;
            p->state = (b == FRAME_SOF) ? RX_LEN : RX_SOF;
        } else {
            p->frame.len = b;
            p->idx = 0;
            p->state = RX_TYPE;
        }
        break;
    case RX_TYPE:
        p->frame.type = b;
        p->state = p->frame.len ? RX_PAYLOAD : RX_CRC_HI;
        break;
    case RX_PAYLOAD:
        p->frame.payload[p->idx++] = b;
        if (p->idx >= p->frame.len) p->state = RX_CRC_HI;
        break;
    case RX_CRC_HI:
        p->crc_hi = b;
        p->state = RX_CRC_LO;
        break;
    case RX_CRC_LO: {
        uint8_t tmp[FRAME_MAX_PAYLOAD + 2];
        tmp[0] = p->frame.len;
        tmp[1] = p->frame.type;
        for (uint8_t i = 0; i < p->frame.len; i++) tmp[2 + i] = p->frame.payload[i];
        uint16_t want = crc16_ccitt(tmp, (size_t)p->frame.len + 2u);
        uint16_t got  = (uint16_t)((uint16_t)p->crc_hi << 8 | b);
        p->state = RX_SOF;
        if (want == got) return 1;
        p->crc_errors++;
        break;
    }
    }
    return 0;
}
