//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "COMPLETABLE8IMPACT8POINT.HPP"

namespace FORRADIA8GAME {
    class OBJECT {
      public:
        OBJECT(int type);

        OBJECT(std::string_view typeName);

        int mType{0};
        int mQuantity{1};
        std::vector<COMPLETABLE8IMPACT8POINT> mImpactPoints;
    };
}