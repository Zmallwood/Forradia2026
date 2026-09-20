/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "MouseUtilities.hpp"

namespace Forradia
{
    PointF GetMousePosition()
    {
        auto canvas_size{GetCanvasSize()};

        int x;
        int y;

        SDL_GetMouseState(&x, &y);

        return PointF{static_cast<float>(x) / canvas_size.width,
                      static_cast<float>(y) / canvas_size.height};
    }
}