/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "CanvasUtilities.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    size get_canvas_size()
    {
        int width{0};
        int height{0};

        SDL_GetWindowSize(_<sdl_device>().window_.get(), &width, &height);

        return {width, height};
    }

    float get_aspect_ratio()
    {
        auto size{get_canvas_size()};

        return static_cast<float>(size.width) / size.height;
    }

    float convert_width_to_height(float width)
    {
        return width * get_aspect_ratio();
    }

    float convert_height_to_width(float height)
    {
        return height / get_aspect_ratio();
    }
}