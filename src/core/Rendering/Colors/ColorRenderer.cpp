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
        auto canvas_size{GetCanvasSize()};

        auto dest_x{static_cast<int>(x * canvas_size.width)};
        auto dest_y{static_cast<int>(y * canvas_size.height)};
        auto dest_width{static_cast<int>(width * canvas_size.width)};
        auto dest_height{static_cast<int>(height * canvas_size.height)};

        auto rect{SDL_Rect{dest_x, dest_y, dest_width, dest_height}};

        auto sdl_color{color.ToSDLColor()};

        SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdl_color.r,
                               sdl_color.g, sdl_color.b, sdl_color.a);

        SDL_RenderFillRect(_<SDLDevice>().renderer_.get(), &rect);
    }

    void ColorRenderer::DrawLine(float x1, float y1, float x2, float y2,
                                 Color color)
    {
        auto canvas_size{GetCanvasSize()};

        auto dest_x1{static_cast<int>(x1 * canvas_size.width)};
        auto dest_y1{static_cast<int>(y1 * canvas_size.height)};
        auto dest_x2{static_cast<int>(x2 * canvas_size.width)};
        auto dest_y2{static_cast<int>(y2 * canvas_size.height)};

        auto sdl_color{color.ToSDLColor()};

        SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdl_color.r,
                               sdl_color.g, sdl_color.b, sdl_color.a);

        SDL_RenderDrawLine(_<SDLDevice>().renderer_.get(), dest_x1, dest_y1,
                           dest_x2, dest_y2);
    }
}