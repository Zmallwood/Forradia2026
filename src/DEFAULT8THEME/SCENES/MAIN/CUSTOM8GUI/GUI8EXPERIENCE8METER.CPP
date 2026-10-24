//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8EXPERIENCE8METER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "DEFAULT8THEME/THEME8MATH/EXPERIENCE8MATH.HPP"

namespace FORRADIA8GAME {
    GUI8EXPERIENCE8METER::GUI8EXPERIENCE8METER()
        : GUI8METER(0.0F, 0.985F, 1.0F, 0.015F) {
    }

    float
    GUI8EXPERIENCE8METER::GET8METER8PROGRESS() {
        auto experience{_<PLAYER>().mExperience};
        auto progress{CALCULATE8FRACTIONAL8EXPERIENCE8PROGRESS(experience)};
        return progress;
    }
}