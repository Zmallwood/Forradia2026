//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class OBJECT;

    class PLAYER8EQUIPMENT {
      public:
        PLAYER8EQUIPMENT();

        std::map<int, std::shared_ptr<OBJECT>> slots_;
    };
}