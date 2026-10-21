//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "MOUSE8UTILITIES.HPP"

namespace FORRADIA8GAME {
    POINT8F
    GET8MOUSE8POSITION() {
        auto canvasSize{GET8CANVAS8SIZE()};

        int x;
        int y;

        SDL_GetMouseState(&x, &y);

        return {static_cast<float>(x) / canvasSize.width,
                static_cast<float>(y) / canvasSize.height};
    }
}