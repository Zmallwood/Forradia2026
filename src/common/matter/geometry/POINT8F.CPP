// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "POINT8F.HPP"

void
POINT8F::operator+=(const POINT8F &other)
{
    x += other.x;
    y += other.y;
}

POINT8F
POINT8F::operator+(const POINT8F &other) const
{
    return {x + other.x, y + other.y};
}

POINT8F
POINT8F::operator-(const POINT8F &other) const
{
    return {x - other.x, y - other.y};
}