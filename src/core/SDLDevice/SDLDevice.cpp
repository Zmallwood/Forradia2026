/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "SDLDevice.hpp"

namespace Forradia
{
    SDLDevice::SDLDevice()
    {
        auto windowFlags{SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP};

        window_ = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(k_windowName_.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags),
            SDLDeleter());

        renderer_ = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
            SDLDeleter());
    }

    void SDLDevice::ClearCanvas()
    {
        SDL_SetRenderDrawColor(renderer_.get(), 0, 150, 255, 255);
        SDL_RenderClear(renderer_.get());
    }

    void SDLDevice::PresentCanvas()
    {
        SDL_RenderPresent(renderer_.get());
    }

    void SDLDevice::Clip(float x, float y, float width, float height)
    {
        SDL_Rect clipRect;

        auto canvasSize{GetCanvasSize()};

        clipRect.x = static_cast<int>(x * canvasSize.width);
        clipRect.y = static_cast<int>(y * canvasSize.height);
        clipRect.w = static_cast<int>(width * canvasSize.width);
        clipRect.h = static_cast<int>(height * canvasSize.height);

        SDL_RenderSetClipRect(renderer_.get(), &clipRect);
    }

    void SDLDevice::ResetClip()
    {
        SDL_RenderSetClipRect(renderer_.get(), nullptr);
    }
}