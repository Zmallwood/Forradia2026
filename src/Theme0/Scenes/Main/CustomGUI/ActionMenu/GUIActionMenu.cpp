/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIActionMenu.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/MinorComponents/Cursor.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    void GUIActionMenu::OnMouseDown(Uint8 mouseButton)
    {
        auto mousePosition{GetMousePosition()};

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
                GUIActionMenuEntry entry;
                entry.label = "Plan wood wall north, plank 1";
                entry.action = []() {};

                entries_.push_back(entry);
            }
        }
        else if (mouseButton == SDL_BUTTON_LEFT)
        {
            visible_ = false;

            auto row{1};

            for (auto &entry : entries_)
            {
                auto bounds{
                    RectF{rightClickMousePosition_.x,
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
}