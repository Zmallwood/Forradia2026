//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8ESSENCE8PANEL.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/SUB/ESSENCE8SYSTEM.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"

namespace FORRADIA8GAME {
    GUI8ESSENCE8PANEL::GUI8ESSENCE8PANEL()
        : GUI8PANEL(0.2F, 0.0F, 0.36F, 0.23F) {
    }

    void
    GUI8ESSENCE8PANEL::RENDER8DERIVED() {
        GUI8PANEL::RENDER8DERIVED();

        auto position{GET8POSITION()};

        _<TEXT8RENDERER>().DRAW8STRING("You notice:", position.x + 0.015F,
                                       position.y + 0.01F, FONT8SIZES::_15,
                                       false, COLORS::kGold);

        for (auto i = 0; i < _<ESSENCE8SYSTEM>().kMaxDescriptions_; i++) {
            auto description{_<ESSENCE8SYSTEM>().GET8ESSENCE8DESCRIPTION(i)};

            auto randomColor{(description.size() * 3 + i) % 4};

            COLOR color{COLORS::kWhite};

            switch (randomColor) {
            case 0:
                color = COLORS::kYellowGray;
                break;
            case 1:
                color = COLORS::kGold;
                break;
            case 2:
                color = COLORS::kWhite;
                break;
            case 3:
                color = COLORS::kWheat;
                break;
            default:
                color = COLORS::kWhite;
                break;
            }

            _<TEXT8RENDERER>().DRAW8STRING(description, position.x + 0.015F,
                                           position.y + 0.01F +
                                               ((i + 1) * 0.03F),
                                           FONT8SIZES::_15, false, color);
        }
    }
}