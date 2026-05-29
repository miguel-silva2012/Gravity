#pragma once

#include <stdint.h>

typedef struct {
    double x, y;
    double velx, vely;
    double accx, accy;
    const unsigned short mass;
    const uint8_t r;
} Rect;