#ifndef SERVO_CRC16_H
#define SERVO_CRC16_H
#include <stdint.h>
#include <stddef.h>

/* CRC-16/CCITT-FALSE: poly 0x1021, init 0xFFFF, no reflection, xorout 0.
 * Check value for "123456789" is 0x29B1. */
uint16_t crc16_ccitt(const uint8_t *data, size_t len);

#endif
