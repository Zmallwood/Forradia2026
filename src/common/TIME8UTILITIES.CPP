//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "TIME8UTILITIES.HPP"

namespace FORRADIA8GAME {
    int
    NOW() {
        return SDL_GetTicks();
    }
}