/* SPDX-License-Identifier: GPL-3.0-or-later */
#ifndef HOOFTTY_PONY_TYPES_H
#define HOOFTTY_PONY_TYPES_H

#include <stdint.h>

typedef struct {
    uint16_t width;
    uint16_t height;
    const uint8_t *pixels;
} PonySprite;

#endif
