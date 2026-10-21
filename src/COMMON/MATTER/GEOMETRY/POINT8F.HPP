//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class POINT8F {
      public:
        void operator+=(const POINT8F &other);

        POINT8F operator+(const POINT8F &other) const;

        POINT8F operator-(const POINT8F &other) const;

        float x{0.0F};
        float y{0.0F};
    };
}