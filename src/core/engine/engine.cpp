// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "ENGINE.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/MINOR_COMPONENTS/CURSOR.HPP"
#include "CORE/MINOR_COMPONENTS/FPS_COUNTER.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "CORE/SDL_DEVICE/SDL_DEVICE.HPP"
#include "CORE/SCENES_CORE/SCENE_MANAGER.HPP"

void ENGINE::START()
{
    srand(time(nullptr));

    _<IMAGE8BANK>().LOAD8IMAGES();

    _<TextRenderer>().Initialize();

    while (running_)
    {
        POLL_EVENTS();

        _<Cursor>().Reset();

        _<SceneManager>().UpdateCurrentScene();

        _<FPSCounter>().Update();

        _<SDLDevice>().ClearCanvas();

        _<SceneManager>().RenderCurrentScene();

        _<FPSCounter>().Render();

        _<Cursor>().Render();

        _<SDLDevice>().PresentCanvas();
    }
}

void ENGINE::POLL_EVENTS()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            running_ = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            _<SceneManager>().OnKeyDownCurrentScene(event.key.keysym.sym);

            break;
        }
        case SDL_KEYUP:
        {
            _<SceneManager>().OnKeyUpCurrentScene(event.key.keysym.sym);

            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            _<SceneManager>().OnMouseDownCurrentScene(event.button.button);

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                ticksLeftMouseButtonDown_ = NOW();
                break;
            case SDL_BUTTON_RIGHT:
                ticksRightMouseButtonDown_ = NOW();
                break;
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            auto clickSpeed = 0;

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                clickSpeed = NOW() - ticksLeftMouseButtonDown_;
                break;
            case SDL_BUTTON_RIGHT:
                clickSpeed = NOW() - ticksRightMouseButtonDown_;
                break;
            }
            
            _<SceneManager>().OnMouseUpCurrentScene(event.button.button,
                                                    clickSpeed);
            break;
        }
        }
    }
}

void ENGINE::STOP()
{
    running_ = false;
}