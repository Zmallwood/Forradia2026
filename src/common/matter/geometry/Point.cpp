// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "POINT.HPP"

POINT
POINT::operator+(const POINT &other) const
{
    return {x + other.x, y + other.y};
}