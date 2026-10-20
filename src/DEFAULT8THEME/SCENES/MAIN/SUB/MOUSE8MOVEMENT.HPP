//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class MOUSE8MOVEMENT {
      public:
        void UPDATE();

        void ON8KEY8DOWN(SDL_Keycode key);

        void ON8KEY8UP(SDL_Keycode key);

        void ON8MOUSE8DOWN(Uint8 button);

      private:
        bool ctrlKeyDown_{false};
    };
}