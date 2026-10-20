//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA
{
    class WORLD8AREA;

    class WORLD
    {
      public:
        WORLD();

        std::shared_ptr<WORLD8AREA> currentWorldArea_;
    };
}