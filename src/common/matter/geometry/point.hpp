//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class POINT
    {
      public:
        auto operator<=>(const POINT &) const = default;

        POINT operator+(const POINT &other) const;

        int x = 0;
        int y = 0;
    };
}