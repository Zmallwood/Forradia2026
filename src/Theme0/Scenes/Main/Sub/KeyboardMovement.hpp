/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class KeyboardMovement
    {
      public:
        void Update();

        void OnKeyDown(SDL_Keycode key);

        void OnKeyUp(SDL_Keycode key);

      private:
        std::set<SDL_Keycode> pressedKeys_;
    };
}