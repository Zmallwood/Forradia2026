//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "SDL8DEVICE.HPP"

namespace FORRADIA
{
    SDL8DEVICE::SDL8DEVICE()
    {
        auto windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;

        window_ = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(kWindowName_.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags),
            SDL8DELETER());

        renderer_ = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
            SDL8DELETER());
    }

    void
    SDL8DEVICE::CLEAR8CANVAS()
    {
        SDL_SetRenderDrawColor(renderer_.get(), 0, 150, 255, 255);
        SDL_RenderClear(renderer_.get());
    }

    void
    SDL8DEVICE::PRESENT8CANVAS()
    {
        SDL_RenderPresent(renderer_.get());
    }

    void
    SDL8DEVICE::CLIP(float x, float y, float width, float height)
    {
        SDL_Rect clipRect;

        auto canvasSize = GET8CANVAS8SIZE();

        clipRect.x = static_cast<int>(x * canvasSize.width);
        clipRect.y = static_cast<int>(y * canvasSize.height);
        clipRect.w = static_cast<int>(width * canvasSize.width);
        clipRect.h = static_cast<int>(height * canvasSize.height);

        SDL_RenderSetClipRect(renderer_.get(), &clipRect);
    }

    void
    SDL8DEVICE::RESET8CLIP()
    {
        SDL_RenderSetClipRect(renderer_.get(), nullptr);
    }
}