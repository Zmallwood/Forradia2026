/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "sdl_device.hpp"

namespace Forradia
{
    sdl_device::sdl_device()
    {
        auto window_flags{SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP};

        window_ = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(k_window_name_.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 600, window_flags),
            sdl_deleter());

        renderer_ = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
            sdl_deleter());
    }

    void sdl_device::clear_canvas()
    {
        SDL_SetRenderDrawColor(renderer_.get(), 0, 150, 255, 255);
        SDL_RenderClear(renderer_.get());
    }

    void sdl_device::present_canvas()
    {
        SDL_RenderPresent(renderer_.get());
    }

    void sdl_device::clip(float x, float y, float width, float height)
    {
        SDL_Rect clip_rect;

        auto canvas_size{get_canvas_size()};

        clip_rect.x = static_cast<int>(x * canvas_size.width);
        clip_rect.y = static_cast<int>(y * canvas_size.height);
        clip_rect.w = static_cast<int>(width * canvas_size.width);
        clip_rect.h = static_cast<int>(height * canvas_size.height);

        SDL_RenderSetClipRect(renderer_.get(), &clip_rect);
    }

    void sdl_device::reset_clip()
    {
        SDL_RenderSetClipRect(renderer_.get(), nullptr);
    }
}