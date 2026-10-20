//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class OBJECT;

    class POSITIONED8OBJECT
    {
      public:
        POINT position_ = {-1, -1};
        std::shared_ptr<OBJECT> object_;
    };
}