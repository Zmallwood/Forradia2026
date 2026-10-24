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

        mInitialized = true;

        auto windowName{_<GAME8PROPERTIES>().mkWindowName};
        auto windowFlags{SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP};

        mWindow = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(windowName.data(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags),
            SDL8DELETER());

        mRenderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED),
            SDL8DELETER());
    }

    SDL8DEVICE::~SDL8DEVICE() {
        if (mWindow)
            SDL_SetWindowFullscreen(mWindow.get(), 0);

        if (mInitialized) {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
            }
        }

        mRenderer.reset();
        mWindow.reset();

        if (!mInitialized)
            return;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void
    SDL8DEVICE::CLEAR8CANVAS() {
        SDL_SetRenderDrawColor(mRenderer.get(), 0, 150, 255, 255);
        SDL_RenderClear(mRenderer.get());
    }

    void
    SDL8DEVICE::PRESENT8CANVAS() {
        SDL_RenderPresent(mRenderer.get());
    }

    void
    SDL8DEVICE::CLIP(float x, float y, float width, float height) {
        SDL_Rect clipRect;

        auto canvasSize{GET8CANVAS8SIZE()};

        clipRect.x = static_cast<int>(x * canvasSize.width);
        clipRect.y = static_cast<int>(y * canvasSize.height);
        clipRect.w = static_cast<int>(width * canvasSize.width);
        clipRect.h = static_cast<int>(height * canvasSize.height);

        SDL_RenderSetClipRect(mRenderer.get(), &clipRect);
    }

    void
    SDL8DEVICE::RESET8CLIP() {
        SDL_RenderSetClipRect(mRenderer.get(), nullptr);
    }
}