//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class COLOR {
      public:
        SDL_Color TO8SDL8COLOR();

        float red{0.0F};
        float green{0.0F};
        float blue{0.0F};
        float alpha{1.0F};
    };
}