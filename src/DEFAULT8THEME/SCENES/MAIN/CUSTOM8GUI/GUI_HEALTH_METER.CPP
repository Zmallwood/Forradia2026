//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI_HEALTH_METER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"

namespace FORRADIA
{
    GUIHealthMeter::GUIHealthMeter() : GUI8METER(0.1f, 0.08f, 0.08f, 0.015f)
    {
    }

    float
    GUIHealthMeter::GET8METER8PROGRESS()
    {
        return _<PLAYER>().health_ / _<PLAYER>().maxHealth_;
    }

    COLOR
    GUIHealthMeter::GET8FILLED8COLOR()
    {
        return COLORS::kRed;
    }
}