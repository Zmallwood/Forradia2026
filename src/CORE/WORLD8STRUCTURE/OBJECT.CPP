//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "OBJECT.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"

namespace FORRADIA8GAME {
    OBJECT::OBJECT(int type) : type_(type) {
        auto impactPoints = _<OBJECT8INDEX>().GET8IMPACT8POINTS(type);

        for (auto impactPoint : impactPoints) {
            impactPoints_.push_back(COMPLETABLE8IMPACT8POINT{impactPoint});
        }
    }

    OBJECT::OBJECT(std::string_view typeName) : OBJECT(HASH(typeName)) {
    }
}