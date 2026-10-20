//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8EXPERIENCE8METER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "DEFAULT8THEME/THEME8MATH/EXPERIENCE_MATH.HPP"

namespace FORRADIA8GAME
{
    GUI8EXPERIENCE8METER::GUI8EXPERIENCE8METER()
        : GUI8METER(0.0f, 0.985f, 1.0f, 0.015f)
    {
    }

    float
    GUI8EXPERIENCE8METER::GET8METER8PROGRESS()
    {
        auto experience = _<PLAYER>().experience_;

        auto progress = CalculateFractionalExperienceProgress(experience);

        return progress;
    }
}