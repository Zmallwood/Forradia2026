//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8STATUS8PANEL.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "DEFAULT8THEME/THEME8MATH/EXPERIENCE8MATH.HPP"
#include "GUI8HEALTH8METER.HPP"

namespace FORRADIA8GAME {
    GUI8STATUS8PANEL::GUI8STATUS8PANEL() : GUI8PANEL(0.0F, 0.0F, 0.2F, 0.2F) {
        ADD8COMPONENT(std::make_shared<GUI8HEALTH8METER>());
    }

    void
    GUI8STATUS8PANEL::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        _<TEXT8RENDERER>().DRAW8STRING(_<PLAYER>().mName, 0.015F, 0.01F,
                                       FONT8SIZES::_20, false);

        auto playerLevel{CALCULATE8CURRENT8LEVEL(_<PLAYER>().mExperience)};

        std::string levelText{"Level " + std::to_string(playerLevel)};

        _<TEXT8RENDERER>().DRAW8STRING(levelText, 0.015F, 0.04F,
                                       FONT8SIZES::_25, false,
                                       COLORS::kYellowGray);

        std::stringstream ssHealth;

        ssHealth << std::fixed << std::setprecision(1)
                 << "Health: " << _<PLAYER>().mHealth << "/"
                 << _<PLAYER>().mMaxHealth;

        _<TEXT8RENDERER>().DRAW8STRING(ssHealth.str(), 0.015F, 0.08F,
                                       FONT8SIZES::_15, false, COLORS::kWheat);
    }
}