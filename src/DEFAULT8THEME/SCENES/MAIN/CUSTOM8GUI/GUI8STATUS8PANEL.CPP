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
    GUI8STATUS8PANEL::GUI8STATUS8PANEL() : GUI8PANEL(0.0f, 0.0f, 0.2f, 0.2f) {
        ADD8COMPONENT(std::make_shared<GUI8HEALTH8METER>());
    }

    void
    GUI8STATUS8PANEL::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        _<TEXT8RENDERER>().DRAW8STRING(_<PLAYER>().name_, 0.015f, 0.01f,
                                       FONT8SIZES::_18, false);

        auto playerLevel = CALCULATE8CURRENT8LEVEL(_<PLAYER>().experience_);

        std::string levelText = "Level " + std::to_string(playerLevel);

        _<TEXT8RENDERER>().DRAW8STRING(levelText, 0.015f, 0.04f,
                                       FONT8SIZES::_24, false,
                                       COLORS::kYellowGray);

        std::stringstream ssHealth;

        ssHealth << std::fixed << std::setprecision(1)
                 << "Health: " << _<PLAYER>().health_ << "/"
                 << _<PLAYER>().maxHealth_;

        _<TEXT8RENDERER>().DRAW8STRING(ssHealth.str(), 0.015f, 0.08f,
                                       FONT8SIZES::_12, false, COLORS::kWheat);
    }
}