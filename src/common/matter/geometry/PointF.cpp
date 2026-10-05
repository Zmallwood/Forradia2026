// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "PointF.hpp"

void PointF::operator+=(const PointF &other)
{
    x += other.x;
    y += other.y;
}

PointF PointF::operator+(const PointF &other) const
{
    return {x + other.x, y + other.y};
}

PointF PointF::operator-(const PointF &other) const
{
    return {x - other.x, y - other.y};
}