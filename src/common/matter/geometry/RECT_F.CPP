// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "RECT_F.HPP"

bool RECT_F::CONTAINS(POINT_F point)
{
    return point.x >= x && point.x <= x + width && point.y >= y &&
           point.y <= y + height;
}