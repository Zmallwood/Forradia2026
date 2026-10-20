//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8ACTION8MENU.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
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
        auto mousePosition = GET8MOUSE8POSITION();

        auto tileUnitsWidth = _<GAME8PROPERTIES>().kTileUnitsWidth_;

        if (mouseButton == SDL_BUTTON_RIGHT) {
            visible_ = true;

            entries_.clear();

            rightClickMousePosition_ = mousePosition;

            auto worldArea = _<WORLD>().currentWorldArea_;

            auto facedTileCoordinate = _<PLAYER>().facedTileCoordinate_;

            auto tile = worldArea->GET8TILE(facedTileCoordinate);

            auto ground = tile->ground_;

            if (ground != HASH("GroundWater")) {
                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallNorthPlank1;
                entryPlannedWoodWallNorthPlank1.label =
                    "Plan wood wall north, plank 1";
                entryPlannedWoodWallNorthPlank1.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallNorthPlank1",
                        {tileUnitsWidth / 4 * 0 + tileUnitsWidth / 8, 0});
                };

                entries_.push_back(entryPlannedWoodWallNorthPlank1);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallNorthPlank2;
                entryPlannedWoodWallNorthPlank2.label =
                    "Plan wood wall north, plank 2";
                entryPlannedWoodWallNorthPlank2.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallNorthPlank2",
                        {tileUnitsWidth / 4 * 1 + tileUnitsWidth / 8, 0});
                };

                entries_.push_back(entryPlannedWoodWallNorthPlank2);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallNorthPlank3;
                entryPlannedWoodWallNorthPlank3.label =
                    "Plan wood wall north, plank 3";
                entryPlannedWoodWallNorthPlank3.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallNorthPlank3",
                        {tileUnitsWidth / 4 * 2 + tileUnitsWidth / 8, 0});
                };

                entries_.push_back(entryPlannedWoodWallNorthPlank3);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallNorthPlank4;
                entryPlannedWoodWallNorthPlank4.label =
                    "Plan wood wall north, plank 4";
                entryPlannedWoodWallNorthPlank4.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallNorthPlank4",
                        {tileUnitsWidth / 4 * 3 + tileUnitsWidth / 8, 0});
                };

                entries_.push_back(entryPlannedWoodWallNorthPlank4);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallEastPlank1;
                entryPlannedWoodWallEastPlank1.label =
                    "Plan wood wall east, plank 1";
                entryPlannedWoodWallEastPlank1.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallEastPlank1",
                        {tileUnitsWidth - 1,
                         tileUnitsWidth / 4 * 0 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallEastPlank1);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallEastPlank2;
                entryPlannedWoodWallEastPlank2.label =
                    "Plan wood wall east, plank 2";
                entryPlannedWoodWallEastPlank2.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallEastPlank2",
                        {tileUnitsWidth - 1,
                         tileUnitsWidth / 4 * 1 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallEastPlank2);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallEastPlank3;
                entryPlannedWoodWallEastPlank3.label =
                    "Plan wood wall east, plank 3";
                entryPlannedWoodWallEastPlank3.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallEastPlank3",
                        {tileUnitsWidth - 1,
                         tileUnitsWidth / 4 * 2 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallEastPlank3);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallEastPlank4;
                entryPlannedWoodWallEastPlank4.label =
                    "Plan wood wall east, plank 4";
                entryPlannedWoodWallEastPlank4.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallEastPlank4",
                        {tileUnitsWidth - 1,
                         tileUnitsWidth / 4 * 3 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallEastPlank4);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallSouthPlank1;
                entryPlannedWoodWallSouthPlank1.label =
                    "Plan wood wall south, plank 1";
                entryPlannedWoodWallSouthPlank1.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallSouthPlank1",
                        {tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                             tileUnitsWidth / 4 * 0 + tileUnitsWidth / 8,
                         tileUnitsWidth - 1});
                };

                entries_.push_back(entryPlannedWoodWallSouthPlank1);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallSouthPlank2;
                entryPlannedWoodWallSouthPlank2.label =
                    "Plan wood wall south, plank 2";
                entryPlannedWoodWallSouthPlank2.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallSouthPlank2",
                        {tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                             tileUnitsWidth / 4 * 1 + tileUnitsWidth / 8,
                         tileUnitsWidth - 1});
                };

                entries_.push_back(entryPlannedWoodWallSouthPlank2);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallSouthPlank3;
                entryPlannedWoodWallSouthPlank3.label =
                    "Plan wood wall south, plank 3";
                entryPlannedWoodWallSouthPlank3.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallSouthPlank3",
                        {tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                             tileUnitsWidth / 4 * 2 + tileUnitsWidth / 8,
                         tileUnitsWidth - 1});
                };

                entries_.push_back(entryPlannedWoodWallSouthPlank3);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallSouthPlank4;
                entryPlannedWoodWallSouthPlank4.label =
                    "Plan wood wall south, plank 4";
                entryPlannedWoodWallSouthPlank4.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallSouthPlank4",
                        {tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                             tileUnitsWidth / 4 * 3 + tileUnitsWidth / 8,
                         tileUnitsWidth - 1});
                };

                entries_.push_back(entryPlannedWoodWallSouthPlank4);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallWestPlank1;
                entryPlannedWoodWallWestPlank1.label =
                    "Plan wood wall west, plank 1";
                entryPlannedWoodWallWestPlank1.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallWestPlank1",
                        {0, tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                                tileUnitsWidth / 4 * 0 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallWestPlank1);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallWestPlank2;
                entryPlannedWoodWallWestPlank2.label =
                    "Plan wood wall west, plank 2";
                entryPlannedWoodWallWestPlank2.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallWestPlank2",
                        {0, tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                                tileUnitsWidth / 4 * 1 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallWestPlank2);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallWestPlank3;
                entryPlannedWoodWallWestPlank3.label =
                    "Plan wood wall west, plank 3";
                entryPlannedWoodWallWestPlank3.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallWestPlank3",
                        {0, tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                                tileUnitsWidth / 4 * 2 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallWestPlank3);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodWallWestPlank4;
                entryPlannedWoodWallWestPlank4.label =
                    "Plan wood wall west, plank 4";
                entryPlannedWoodWallWestPlank4.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodWallWestPlank4",
                        {0, tileUnitsWidth - 1 - tileUnitsWidth / 4 -
                                tileUnitsWidth / 4 * 3 + tileUnitsWidth / 8});
                };

                entries_.push_back(entryPlannedWoodWallWestPlank4);

                GUI8ACTION8MENU8ENTRY entryPlannedWoodFloor;
                entryPlannedWoodFloor.label = "Plan wood floor";
                entryPlannedWoodFloor.action = [=]() {
                    auto tileObjects = tile->tileObjects_;

                    tileObjects->ADD8OBJECT(
                        "ObjectPlannedWoodFloor",
                        {tileUnitsWidth / 2, tileUnitsWidth / 2});
                };

                entries_.push_back(entryPlannedWoodFloor);
            }
        } else if (mouseButton == SDL_BUTTON_LEFT && visible_) {
            visible_ = false;

            auto row = 1;

            for (auto &entry : entries_) {
                RECT8F bounds = {rightClickMousePosition_.x,
                                 rightClickMousePosition_.y + row * kLineHeight,
                                 kWidth, kLineHeight};

                if (bounds.CONTAINS(mousePosition)) {
                    auto action = entry.action;

                    action();
                }

                ++row;
            }
        }
    }

    void
    GUI8ACTION8MENU::RENDER() {
        if (!visible_) {
            return;
        }

        auto mousePosition = GET8MOUSE8POSITION();

        auto numEntries = entries_.size();

        _<COLOR8RENDERER>().FILL8RECT(
            rightClickMousePosition_.x, rightClickMousePosition_.y, kWidth,
            kLineHeight * (numEntries + 1), COLORS::kDarkBlueGray);

        auto marginX = kMarginX;

        auto marginY = CONVERT8WIDTH8TO8HEIGHT(kMarginX);

        _<TEXT8RENDERER>().DRAW8STRING("Actions",
                                       rightClickMousePosition_.x + marginX,
                                       rightClickMousePosition_.y + marginY,
                                       FONT8SIZES::_12, false, COLORS::kGold);

        auto row = 1;

        for (auto &entry : entries_) {
            RECT8F bounds = {rightClickMousePosition_.x,
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