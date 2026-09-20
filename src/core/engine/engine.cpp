/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Engine.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/ScenesCore/SceneManager.hpp"

namespace Forradia
{
    void Engine::Start()
    {
        srand(time(nullptr));

        _<ImageBank>().LoadImages();

        while (running_)
        {
            PollEvents();

            _<SceneManager>().UpdateCurrentScene();

            _<SDLDevice>().ClearCanvas();

            _<SceneManager>().RenderCurrentScene();

            _<SDLDevice>().PresentCanvas();
        }
    }

    void Engine::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running_ = false;
                break;
            case SDL_KEYDOWN:
                _<SceneManager>().OnKeyDownCurrentScene(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _<SceneManager>().OnKeyUpCurrentScene(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _<SceneManager>().OnMouseDownCurrentScene(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _<SceneManager>().OnMouseUpCurrentScene(event.button.button,
                                                        event.button.clicks);
                break;
            }
        }
    }
}