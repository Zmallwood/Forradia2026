/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "engine.hpp"
#include "Core/Assets/image_bank.hpp"
#include "Core/SDLDevice/sdl_device.hpp"
#include "Core/ScenesCore/scene_manager.hpp"

namespace Forradia
{
    void engine::start()
    {
        srand(time(nullptr));

        _<image_bank>().load_images();

        while (running_)
        {
            poll_events();

            _<scene_manager>().update_current_scene();

            _<sdl_device>().clear_canvas();

            _<scene_manager>().render_current_scene();

            _<sdl_device>().present_canvas();
        }
    }

    void engine::poll_events()
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
                _<scene_manager>().on_key_down_current_scene(
                    event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _<scene_manager>().on_key_up_current_scene(
                    event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _<scene_manager>().on_mouse_down_current_scene(
                    event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _<scene_manager>().on_mouse_up_current_scene(
                    event.button.button, event.button.clicks);
                break;
            }
        }
    }
}