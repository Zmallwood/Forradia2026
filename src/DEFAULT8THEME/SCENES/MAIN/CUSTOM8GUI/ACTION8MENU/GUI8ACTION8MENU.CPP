//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8ACTION8MENU.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/MINOR8COMPONENTS/CURSOR.HPP"
#include "CORE/RENDERING/COLORS/COLOR8RENDERER.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"

namespace FORRADIA8GAME {
    void
    GUI8ACTION8MENU::ON8MOUSE8DOWN(Uint8 mouseButton) {
        auto mousePosition{GET8MOUSE8POSITION()};

        auto tileUnitsWidth{_<GAME8PROPERTIES>().kTileUnitsWidth_};

        if (mouseButton == SDL_BUTTON_RIGHT) {
            visible_ = true;

            entries_.clear();

            rightClickMousePosition_ = mousePosition;

            #include "DATA/GUI8ACTION8MENU.ADD8DATA.CPP.INC"
        } else if (mouseButton == SDL_BUTTON_LEFT && visible_) {
            visible_ = false;

            auto row{1};

            for (auto &entry : entries_) {
                RECT8F bounds{rightClickMousePosition_.x,
                              rightClickMousePosition_.y + row * kLineHeight,
                              kWidth, kLineHeight};

                if (bounds.CONTAINS(mousePosition)) {
                    auto action{entry.action};

                    action();
                }

                ++row;
            }
        }
    }

    void
    GUI8ACTION8MENU::RENDER() {
        if (!visible_)
            return;

        auto mousePosition{GET8MOUSE8POSITION()};

        auto numEntries{entries_.size()};

        _<COLOR8RENDERER>().FILL8RECT(
            rightClickMousePosition_.x, rightClickMousePosition_.y, kWidth,
            kLineHeight * (numEntries + 1), COLORS::kDarkBlueGray);

        auto marginX{kMarginX};

        auto marginY{CONVERT8WIDTH8TO8HEIGHT(kMarginX)};

        _<TEXT8RENDERER>().DRAW8STRING("Actions",
                                       rightClickMousePosition_.x + marginX,
                                       rightClickMousePosition_.y + marginY,
                                       FONT8SIZES::_15, false, COLORS::kGold);

        auto row{1};

        for (auto &entry : entries_) {
            RECT8F bounds{rightClickMousePosition_.x,
                          rightClickMousePosition_.y + row * kLineHeight,
                          kWidth, kLineHeight};

            if (bounds.CONTAINS(mousePosition)) {
                _<COLOR8RENDERER>().FILL8RECT(bounds, COLORS::kBlueGray);

                _<CURSOR>().cursorStyle_ = CURSOR8STYLES::Hovering;
            }

            _<TEXT8RENDERER>().DRAW8STRING(
                entry.label, rightClickMousePosition_.x + marginX,
                rightClickMousePosition_.y + marginY + row * kLineHeight);

            ++row;
        }
    }
}