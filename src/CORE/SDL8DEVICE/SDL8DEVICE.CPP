//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "SDL8DEVICE.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"

namespace FORRADIA8GAME {
    SDL8DEVICE::SDL8DEVICE() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "Failed to initialize SDL: " << SDL_GetError()
                      << std::endl;
            return;
        }

        if (TTF_Init() < 0) {
            std::cout << "Failed to initialize TTF: " << TTF_GetError()
                      << std::endl;
            return;
        }

        initialized_ = true;

        auto windowName{_<GAME8PROPERTIES>().kWindowName_};
        auto windowFlags{SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP};

        window_ = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(windowName.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags),
            SDL8DELETER());

        renderer_ = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
            SDL8DELETER());
    }

    SDL8DEVICE::~SDL8DEVICE() {
        if (window_)
            SDL_SetWindowFullscreen(window_.get(), 0);

        if (initialized_) {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
            }
        }

        renderer_.reset();
        window_.reset();

        if (!initialized_)
            return;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void
    SDL8DEVICE::CLEAR8CANVAS() {
        SDL_SetRenderDrawColor(renderer_.get(), 0, 150, 255, 255);
        SDL_RenderClear(renderer_.get());
    }

    void
    SDL8DEVICE::PRESENT8CANVAS() {
        SDL_RenderPresent(renderer_.get());
    }

    void
    SDL8DEVICE::CLIP(float x, float y, float width, float height) {
        SDL_Rect clipRect;

        auto canvasSize{GET8CANVAS8SIZE()};

        clipRect.x = static_cast<int>(x * canvasSize.width);
        clipRect.y = static_cast<int>(y * canvasSize.height);
        clipRect.w = static_cast<int>(width * canvasSize.width);
        clipRect.h = static_cast<int>(height * canvasSize.height);

        SDL_RenderSetClipRect(renderer_.get(), &clipRect);
    }

    void
    SDL8DEVICE::RESET8CLIP() {
        SDL_RenderSetClipRect(renderer_.get(), nullptr);
    }
}