/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "PointF.hpp"

namespace Forradia
{
    void PointF::operator+=(const PointF &other)
    {
        x += other.x;
        y += other.y;
    }
}