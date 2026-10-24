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
        mSlots.insert({HEAD, nullptr});
        mSlots.insert({CHEST, nullptr});
        mSlots.insert({LEGS, nullptr});
        mSlots.insert({FEET, nullptr});
        mSlots.insert({RIGHT8HAND, nullptr});
        mSlots.insert({LEFT8HAND, nullptr});
    }
}