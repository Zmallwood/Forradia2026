/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class MouseMovement
    {
      public:
        void Update();

        void OnKeyDown(SDL_Keycode key);

        void OnKeyUp(SDL_Keycode key);

        void OnMouseDown(Uint8 button);

      private:
        bool ctrl_key_down_{false};
    };
}