// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "MOUSE_UTILITIES.HPP"

POINT_F GetMousePosition()
{
    auto canvasSize = GET_CANVAS_SIZE();

    int x;
    int y;

    SDL_GetMouseState(&x, &y);

    return {static_cast<float>(x) / canvasSize.width,
            static_cast<float>(y) / canvasSize.height};
}