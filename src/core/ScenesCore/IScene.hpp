/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class i_scene
    {
      public:
        void update();

        void render();

        virtual void on_enter()
        {
        }

        virtual void on_key_down(SDL_Keycode key)
        {
        }

        virtual void on_key_up(SDL_Keycode key)
        {
        }

        virtual void on_mouse_down(Uint8 button)
        {
        }

        virtual void on_mouse_up(Uint8 button, int click_speed)
        {
        }

      protected:
        virtual void update_derived()
        {
        }

        virtual void render_derived()
        {
        }
    };
}