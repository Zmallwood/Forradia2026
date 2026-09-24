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
        auto canvasSize{GetCanvasSize()};

        int x;
        int y;

        SDL_GetMouseState(&x, &y);

        return {static_cast<float>(x) / canvasSize.width,
                static_cast<float>(y) / canvasSize.height};
    }
}