// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CANVAS_UTILITIES.HPP"
#include "CORE/SDL_DEVICE/SDL_DEVICE.HPP"

SIZE GET_CANVAS_SIZE()
{
    int width = 0;
    int height = 0;

    SDL_GetWindowSize(_<SDLDevice>().window_.get(), &width, &height);

    return {width, height};
}

float GET_ASPECT_RATIO()
{
    auto size = GET_CANVAS_SIZE();

    return static_cast<float>(size.width) / size.height;
}

float CONVERT_WIDTH_TO_HEIGHT(float width)
{
    return width * GET_ASPECT_RATIO();
}

float CONVERT_HEIGHT_TO_WIDTH(float height)
{
    return height / GET_ASPECT_RATIO();
}