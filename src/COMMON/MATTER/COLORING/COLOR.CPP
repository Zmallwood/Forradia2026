//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "COLOR.HPP"

namespace FORRADIA8GAME {
    SDL_Color
    COLOR::TO8SDL8COLOR() {
        return {static_cast<Uint8>(red * 255), static_cast<Uint8>(green * 255),
                static_cast<Uint8>(blue * 255),
                static_cast<Uint8>(alpha * 255)};
    }
}