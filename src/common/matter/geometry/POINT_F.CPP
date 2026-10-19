// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "POINT_F.HPP"

void POINT_F::operator+=(const POINT_F &other)
{
    x += other.x;
    y += other.y;
}

POINT_F POINT_F::operator+(const POINT_F &other) const
{
    return {x + other.x, y + other.y};
}

POINT_F POINT_F::operator-(const POINT_F &other) const
{
    return {x - other.x, y - other.y};
}