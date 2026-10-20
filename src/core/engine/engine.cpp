// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "ENGINE.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/MINOR8COMPONENTS/CURSOR.HPP"
#include "CORE/MINOR8COMPONENTS/FPS8COUNTER.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "CORE/SCENES8CORE/SCENE8MANAGER.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"

void
ENGINE::START()
{
    RANDOMIZE();

    _<IMAGE8BANK>().LOAD8IMAGES();

    _<TEXT8RENDERER>().INITIALIZE();

    while (running_)
    {
        POLL_EVENTS();

        _<CURSOR>().RESET();

        _<SCENE8MANAGER>().UPDATE8CURRENT8SCENE();

        _<FPS8COUNTER>().UPDATE();

        _<SDL8DEVICE>().CLEAR8CANVAS();

        _<SCENE8MANAGER>().RENDER8CURRENT8SCENE();

        _<FPS8COUNTER>().RENDER();

        _<CURSOR>().RENDER();

        _<SDL8DEVICE>().PRESENT8CANVAS();
    }
}

void
ENGINE::RANDOMIZE()
{
    srand(time(nullptr));
}

void
ENGINE::POLL_EVENTS()
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
            _<SCENE8MANAGER>().ON8KEY8DOWN8CURRENT8SCENE(event.key.keysym.sym);

            break;
        }
        case SDL_KEYUP:
        {
            _<SCENE8MANAGER>().ON8KEY8UP8CURRENT8SCENE(event.key.keysym.sym);

            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            _<SCENE8MANAGER>().ON8MOUSE8DOWN8CURRENT8SCENE(event.button.button);

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

            _<SCENE8MANAGER>().ON8MOUSE8UP8CURRENT8SCENE(event.button.button,
                                                         clickSpeed);
            break;
        }
        }
    }
}

void
ENGINE::STOP()
{
    running_ = false;
}