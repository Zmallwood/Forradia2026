// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUIActionMenu.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/MinorComponents/Cursor.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

void GUIActionMenu::OnMouseDown(Uint8 mouseButton)
{
    auto mousePosition{GetMousePosition()};

    auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};

    if (mouseButton == SDL_BUTTON_RIGHT)
    {
        visible_ = true;

        entries_.clear();

        rightClickMousePosition_ = mousePosition;

        auto worldArea{_<World>().currentWorldArea_};

        auto facedTileCoordinate{_<Player>().facedTileCoordinate_};

        auto tile{worldArea->GetTile(facedTileCoordinate)};

        auto ground{tile->ground_};

        if (ground != Hash("GroundWater"))
        {
            GUIActionMenuEntry entryPlannedWoodWallNorthPlank1;
            entryPlannedWoodWallNorthPlank1.label =
                "Plan wood wall north, plank 1";
            entryPlannedWoodWallNorthPlank1.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallNorthPlank1",
                    {tileUnitsWidth / 4 * 0 + tileUnitsWidth / 8, 0});
            };

            entries_.push_back(entryPlannedWoodWallNorthPlank1);

            GUIActionMenuEntry entryPlannedWoodWallNorthPlank2;
            entryPlannedWoodWallNorthPlank2.label =
                "Plan wood wall north, plank 2";
            entryPlannedWoodWallNorthPlank2.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallNorthPlank2",
                    {tileUnitsWidth / 4 * 1 + tileUnitsWidth / 8, 0});
            };

            entries_.push_back(entryPlannedWoodWallNorthPlank2);

            GUIActionMenuEntry entryPlannedWoodWallNorthPlank3;
            entryPlannedWoodWallNorthPlank3.label =
                "Plan wood wall north, plank 3";
            entryPlannedWoodWallNorthPlank3.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallNorthPlank3",
                    {tileUnitsWidth / 4 * 2 + tileUnitsWidth / 8, 0});
            };

            entries_.push_back(entryPlannedWoodWallNorthPlank3);

            GUIActionMenuEntry entryPlannedWoodWallNorthPlank4;
            entryPlannedWoodWallNorthPlank4.label =
                "Plan wood wall north, plank 4";
            entryPlannedWoodWallNorthPlank4.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallNorthPlank4",
                    {tileUnitsWidth / 4 * 3 + tileUnitsWidth / 8, 0});
            };

            entries_.push_back(entryPlannedWoodWallNorthPlank4);

            GUIActionMenuEntry entryPlannedWoodWallEastPlank1;
            entryPlannedWoodWallEastPlank1.label =
                "Plan wood wall east, plank 1";
            entryPlannedWoodWallEastPlank1.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallEastPlank1",
                    {tileUnitsWidth - 1,
                     tileUnitsWidth / 4 * 0 + tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallEastPlank1);

            GUIActionMenuEntry entryPlannedWoodWallEastPlank2;
            entryPlannedWoodWallEastPlank2.label =
                "Plan wood wall east, plank 2";
            entryPlannedWoodWallEastPlank2.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallEastPlank2",
                    {tileUnitsWidth - 1,
                     tileUnitsWidth / 4 * 1 + tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallEastPlank2);

            GUIActionMenuEntry entryPlannedWoodWallEastPlank3;
            entryPlannedWoodWallEastPlank3.label =
                "Plan wood wall east, plank 3";
            entryPlannedWoodWallEastPlank3.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallEastPlank3",
                    {tileUnitsWidth - 1,
                     tileUnitsWidth / 4 * 2 + tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallEastPlank3);

            GUIActionMenuEntry entryPlannedWoodWallEastPlank4;
            entryPlannedWoodWallEastPlank4.label =
                "Plan wood wall east, plank 4";
            entryPlannedWoodWallEastPlank4.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject(
                    "ObjectPlannedWoodWallEastPlank4",
                    {tileUnitsWidth - 1,
                     tileUnitsWidth / 4 * 3 + tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallEastPlank4);

            GUIActionMenuEntry entryPlannedWoodWallWestPlank1;
            entryPlannedWoodWallWestPlank1.label =
                "Plan wood wall west, plank 1";
            entryPlannedWoodWallWestPlank1.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject("ObjectPlannedWoodWallWestPlank1",
                                       {0, tileUnitsWidth - tileUnitsWidth / 4 -
                                               tileUnitsWidth / 4 * 0 +
                                               tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallWestPlank1);

            GUIActionMenuEntry entryPlannedWoodWallWestPlank2;
            entryPlannedWoodWallWestPlank2.label =
                "Plan wood wall west, plank 2";
            entryPlannedWoodWallWestPlank2.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject("ObjectPlannedWoodWallWestPlank2",
                                       {0, tileUnitsWidth - tileUnitsWidth / 4 -
                                               tileUnitsWidth / 4 * 1 +
                                               tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallWestPlank2);

            GUIActionMenuEntry entryPlannedWoodWallWestPlank3;
            entryPlannedWoodWallWestPlank3.label =
                "Plan wood wall west, plank 3";
            entryPlannedWoodWallWestPlank3.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject("ObjectPlannedWoodWallWestPlank3",
                                       {0, tileUnitsWidth - tileUnitsWidth / 4 -
                                               tileUnitsWidth / 4 * 2 +
                                               tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallWestPlank3);

            GUIActionMenuEntry entryPlannedWoodWallWestPlank4;
            entryPlannedWoodWallWestPlank4.label =
                "Plan wood wall west, plank 4";
            entryPlannedWoodWallWestPlank4.action = [=]()
            {
                auto tileObjects{tile->tileObjects_};

                tileObjects->AddObject("ObjectPlannedWoodWallWestPlank4",
                                       {0, tileUnitsWidth - tileUnitsWidth / 4 -
                                               tileUnitsWidth / 4 * 3 +
                                               tileUnitsWidth / 8});
            };

            entries_.push_back(entryPlannedWoodWallWestPlank4);
        }
    }
    else if (mouseButton == SDL_BUTTON_LEFT)
    {
        visible_ = false;

        auto row{1};

        for (auto &entry : entries_)
        {
            auto bounds{RectF{rightClickMousePosition_.x,
                              rightClickMousePosition_.y + row * k_lineHeight,
                              k_width, k_lineHeight}};

            if (bounds.Contains(mousePosition))
            {
                auto action{entry.action};

                action();
            }

            ++row;
        }
    }
}

void GUIActionMenu::Render()
{
    if (!visible_)
    {
        return;
    }

    auto mousePosition{GetMousePosition()};

    auto numEntries{entries_.size()};

    _<ColorRenderer>().FillRect(
        rightClickMousePosition_.x, rightClickMousePosition_.y, k_width,
        k_lineHeight * (numEntries + 1), Colors::k_darkBlueGray);

    auto marginX{k_marginX};

    auto marginY{ConvertWidthToHeight(k_marginX)};

    _<TextRenderer>().DrawString("Actions",
                                 rightClickMousePosition_.x + marginX,
                                 rightClickMousePosition_.y + marginY,
                                 FontSizes::_12, false, Colors::k_gold);

    auto row{1};

    for (auto &entry : entries_)
    {
        auto bounds{RectF{rightClickMousePosition_.x,
                          rightClickMousePosition_.y + row * k_lineHeight,
                          k_width, k_lineHeight}};

        if (bounds.Contains(mousePosition))
        {
            _<ColorRenderer>().FillRect(bounds, Colors::k_blueGray);

            _<Cursor>().cursorStyle_ = CursorStyles::Hovering;
        }

        _<TextRenderer>().DrawString(
            entry.label, rightClickMousePosition_.x + marginX,
            rightClickMousePosition_.y + marginY + row * k_lineHeight);

        ++row;
    }
}