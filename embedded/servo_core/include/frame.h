#ifndef SERVO_FRAME_H
#define SERVO_FRAME_H
#include <stdint.h>
#include <stddef.h>

/* Wire format:  0xA5 | len | type | payload[len] | crc_hi | crc_lo
 * CRC covers len, type and payload. len <= FRAME_MAX_PAYLOAD. */
#define FRAME_SOF          0xA5u
#define FRAME_MAX_PAYLOAD  32u
#define FRAME_OVERHEAD     5u

typedef struct {
    uint8_t type;
    uint8_t len;
    uint8_t payload[FRAME_MAX_PAYLOAD];
} frame_t;

/* Returns bytes written, or 0 if payload too long / buffer too small. */
size_t frame_encode(const frame_t *f, uint8_t *out, size_t out_cap);

typedef enum { RX_SOF, RX_LEN, RX_TYPE, RX_PAYLOAD, RX_CRC_HI, RX_CRC_LO } rx_state_t;

typedef struct {
    rx_state_t state;
    frame_t    frame;
    uint8_t    idx;
    uint8_t    crc_hi;
    uint32_t   crc_errors;   /* diagnostics */
    uint32_t   len_errors;
} frame_parser_t;

void frame_parser_init(frame_parser_t *p);
/* Feed one byte. Returns 1 when a valid frame is complete (in p->frame). */
int  frame_parser_feed(frame_parser_t *p, uint8_t byte);

#endif
