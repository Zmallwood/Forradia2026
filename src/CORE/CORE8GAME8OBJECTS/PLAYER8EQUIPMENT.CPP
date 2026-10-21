//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "PLAYER8EQUIPMENT.HPP"
#include "PLAYER8EQUIPMENT8SLOTS.HPP"

namespace FORRADIA8GAME {
    PLAYER8EQUIPMENT::PLAYER8EQUIPMENT() {
        using namespace PLAYER8EQUIPMENT8SLOTS;
        slots_.insert({HEAD, nullptr});
        slots_.insert({CHEST, nullptr});
        slots_.insert({LEGS, nullptr});
        slots_.insert({FEET, nullptr});
        slots_.insert({RIGHT8HAND, nullptr});
        slots_.insert({LEFT8HAND, nullptr});
    }
}