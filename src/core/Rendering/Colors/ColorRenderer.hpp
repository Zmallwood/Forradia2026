/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class ColorRenderer
    {
      public:
        void FillRect(float x, float y, float width, float height,
                      Color color = Colors::k_black);

        void DrawLine(float x1, float y1, float x2, float y2,
                      Color color = Colors::k_black);
    };
}