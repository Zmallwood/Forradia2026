/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "Core/ScenesCore/i_scene.hpp"

namespace Forradia
{
    class intro_scene : public i_scene
    {
      protected:
        void render_derived() override;

        void on_key_down(SDL_Keycode key) override;

        void on_mouse_down(Uint8 button) override;
    };
}