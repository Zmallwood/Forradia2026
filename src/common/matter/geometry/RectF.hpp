/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class RectF
    {
      public:
        bool Contains(PointF point);

        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};
    };
}