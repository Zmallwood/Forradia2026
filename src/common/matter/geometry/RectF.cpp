/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "RectF.hpp"

namespace Forradia
{
    bool RectF::Contains(PointF point)
    {
        return point.x >= x && point.x <= x + width && point.y >= y &&
               point.y <= y + height;
    }
}