/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class rect_f
    {
      public:
        bool contains(point_f point);

        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};
    };
}