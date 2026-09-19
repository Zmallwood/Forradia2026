/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class color_renderer
    {
      public:
        void fill_rect(float x, float y, float width, float height,
                       color color = colors::k_black);

        void draw_line(float x1, float y1, float x2, float y2,
                       color color = colors::k_black);
    };
}