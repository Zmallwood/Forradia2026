//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8HEALTH8METER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"

namespace FORRADIA8GAME {
    GUI8HEALTH8METER::GUI8HEALTH8METER()
        : GUI8METER(0.11F, 0.08F, 0.08F, 0.015F) {
    }

    float
    GUI8HEALTH8METER::GET8METER8PROGRESS() {
        return _<PLAYER>().mHealth / _<PLAYER>().mMaxHealth;
    }

    COLOR
    GUI8HEALTH8METER::GET8FILLED8COLOR() {
        return COLORS::kRed;
    }
}