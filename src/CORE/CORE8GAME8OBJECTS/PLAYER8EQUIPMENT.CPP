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
        mSlots.insert({kHead, nullptr});
        mSlots.insert({kChest, nullptr});
        mSlots.insert({kLegs, nullptr});
        mSlots.insert({kFeet, nullptr});
        mSlots.insert({kRightHand, nullptr});
        mSlots.insert({kLeftHand, nullptr});
    }
}