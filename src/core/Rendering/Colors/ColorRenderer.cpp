/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ColorRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

void ColorRenderer::FillRect(float x, float y, float width, float height,
                             Color color)
{
    auto rect{CreateSDLRect(x, y, width, height)};

    auto sdlColor{color.ToSDLColor()};

    SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                           sdlColor.g, sdlColor.b, sdlColor.a);

    SDL_RenderFillRect(_<SDLDevice>().renderer_.get(), &rect);
}

void ColorRenderer::FillRect(RectF rect, Color color)
{
    FillRect(rect.x, rect.y, rect.width, rect.height, color);
}

void ColorRenderer::DrawRect(float x, float y, float width, float height,
                             Color color)
{
    auto rect{CreateSDLRect(x, y, width, height)};

    auto sdlColor{color.ToSDLColor()};

    SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                           sdlColor.g, sdlColor.b, sdlColor.a);

    SDL_RenderDrawRect(_<SDLDevice>().renderer_.get(), &rect);
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

    SDL_RenderDrawLine(_<SDLDevice>().renderer_.get(), destX1, destY1, destX2,
                       destY2);
}

SDL_Rect ColorRenderer::CreateSDLRect(float x, float y, float width,
                                      float height)
{
    auto canvasSize{GetCanvasSize()};

    auto destX{static_cast<int>(std::floor(x * canvasSize.width))};
    auto destY{static_cast<int>(std::floor(y * canvasSize.height))};
    auto destWidth{static_cast<int>(std::ceil(width * canvasSize.width))};
    auto destHeight{static_cast<int>(std::ceil(height * canvasSize.height))};

    return SDL_Rect{destX, destY, destWidth, destHeight};
}