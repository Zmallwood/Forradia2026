// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "COLOR_RENDERER.HPP"
#include "CORE/SDL_DEVICE/SDL_DEVICE.HPP"

void ColorRenderer::FillRect(float x, float y, float width, float height,
    COLOR color)
{
    auto rect = CreateSDLRect(x, y, width, height);

    auto sdlColor = color.TO_SDL_COLOR();

    SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                           sdlColor.g, sdlColor.b, sdlColor.a);

    SDL_RenderFillRect(_<SDLDevice>().renderer_.get(), &rect);
}

void ColorRenderer::FillRect(RECT_F rect, COLOR color)
{
    FillRect(rect.x, rect.y, rect.width, rect.height, color);
}

void ColorRenderer::DrawRect(float x, float y, float width, float height,
    COLOR color)
{
    auto rect = CreateSDLRect(x, y, width, height);

    auto sdlColor = color.TO_SDL_COLOR();

    SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                           sdlColor.g, sdlColor.b, sdlColor.a);

    SDL_RenderDrawRect(_<SDLDevice>().renderer_.get(), &rect);
}

void ColorRenderer::DrawLine(float x1, float y1, float x2, float y2,
    COLOR color)
{
    auto canvasSize = GET_CANVAS_SIZE();

    auto destX1 = static_cast<int>(x1 * canvasSize.width);
    auto destY1 = static_cast<int>(y1 * canvasSize.height);
    auto destX2 = static_cast<int>(x2 * canvasSize.width);
    auto destY2 = static_cast<int>(y2 * canvasSize.height);

    auto sdlColor = color.TO_SDL_COLOR();

    SDL_SetRenderDrawColor(_<SDLDevice>().renderer_.get(), sdlColor.r,
                           sdlColor.g, sdlColor.b, sdlColor.a);

    SDL_RenderDrawLine(_<SDLDevice>().renderer_.get(), destX1, destY1, destX2,
                       destY2);
}

SDL_Rect ColorRenderer::CreateSDLRect(float x, float y, float width,
                                      float height)
{
    auto canvasSize = GET_CANVAS_SIZE();

    auto destX = static_cast<int>(std::floor(x * canvasSize.width));
    auto destY = static_cast<int>(std::floor(y * canvasSize.height));
    auto destWidth = static_cast<int>(std::ceil(width * canvasSize.width));
    auto destHeight = static_cast<int>(std::ceil(height * canvasSize.height));

    return SDL_Rect{destX, destY, destWidth, destHeight};
}