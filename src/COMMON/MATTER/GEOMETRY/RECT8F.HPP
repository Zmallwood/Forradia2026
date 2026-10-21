//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class RECT8F {
      public:
        bool CONTAINS(POINT8F point);

        float x{0.0F};
        float y{0.0F};
        float width{0.0F};
        float height{0.0F};
    };
}