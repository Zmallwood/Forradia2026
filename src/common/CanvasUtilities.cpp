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
    Size GetCanvasSize()
    {
        int width{0};
        int height{0};

        SDL_GetWindowSize(_<SDLDevice>().window_.get(), &width, &height);

        return {width, height};
    }

    float GetAspectRatio()
    {
        auto size{GetCanvasSize()};

        return static_cast<float>(size.width) / size.height;
    }

    float ConvertWidthToHeight(float width)
    {
        return width * GetAspectRatio();
    }

    float ConvertHeightToWidth(float height)
    {
        return height / GetAspectRatio();
    }
}