/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Point.hpp"

namespace Forradia
{
    Point Point::operator+(const Point &other) const
    {
        return {x + other.x, y + other.y};
    }
}