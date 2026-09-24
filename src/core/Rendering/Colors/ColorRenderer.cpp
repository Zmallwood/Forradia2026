/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ColorRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    void ColorRenderer::FillRect(float x, float y, float width, float height,
                                 Color color)
    {
        auto canvasSize{GetCanvasSize()};

        auto destX{static_cast<int>(x * canvasSize.width)};
        auto destY{static_cast<int>(y * canvasSize.height)};
        auto destWidth{static_cast<int>(width * canvasSize.width)};
        auto destHeight{static_cast<int>(height * canvasSize.height)};

        auto rect{SDL_Rect{destX, destY, destWidth, destHeight}};

        auto sdlColor{color.ToSDLColor()};

        SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                               sdlColor.g, sdlColor.b, sdlColor.a);

        SDL_RenderFillRect(_<SDLDevice>().renderer_.get(), &rect);
    }

    void ColorRenderer::DrawLine(float x1, float y1, float x2, float y2,
                                 Color color)
    {
        auto canvasSize{GetCanvasSize()};

        auto destX1{static_cast<int>(x1 * canvasSize.width)};
        auto destY1{static_cast<int>(y1 * canvasSize.height)};
        auto destX2{static_cast<int>(x2 * canvasSize.width)};
        auto destY2{static_cast<int>(y2 * canvasSize.height)};

        auto sdlColor{color.ToSDLColor()};

        SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                               sdlColor.g, sdlColor.b, sdlColor.a);

        SDL_RenderDrawLine(_<SDLDevice>().renderer_.get(), destX1, destY1,
                           destX2, destY2);
    }
}