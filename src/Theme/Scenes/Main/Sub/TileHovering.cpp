/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "TileHovering.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    void TileHovering::Update()
    {
        auto mousePosition{GetMousePosition()};

        auto worldArea{_<World>().currentWorldArea_};

        auto playerTile{worldArea->GetTile(_<Player>().position_)};

        if (!playerTile)
        {
            return;
        }

        auto playerElevation{playerTile->elevation_};

        auto tileWidth{GameProperties::k_tileWidth_};
        auto tileHeight{ConvertWidthToHeight(tileWidth)};

        for (auto y = -6; y < 11 + 6; y++)
        {
            for (auto x = -6; x < 11 + 6; x++)
            {
                auto xCoordinate{_<Player>().position_.x - 5 + x};
                auto yCoordinate{_<Player>().position_.y - 5 + y};

                if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                {
                    continue;
                }

                auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                auto elevation{tile->elevation_};

                auto tileX{0.25f - tileWidth / 2 + x * tileWidth / 2 -
                           y * tileWidth / 2};

                auto tileY{0.5f - 5.5f * tileHeight + x * tileHeight / 2 +
                           y * tileHeight / 2 +
                           playerElevation * tileHeight / 4};

                auto centerBottom{
                    PointF{tileX + tileWidth / 2, tileY + tileHeight / 2}};

                auto dxBottom{std::abs(mousePosition.x - centerBottom.x) /
                              (tileWidth / 2)};
                auto dyBottom{std::abs(mousePosition.y - centerBottom.y) /
                              (tileHeight / 2)};
                if (dxBottom + dyBottom <= 1.0f)
                {
                    hoveredCoordinate_ = {xCoordinate, yCoordinate};
                }

                auto elevationHeight{elevation * tileHeight / 4};

                RectF elevationRect{tileX,
                                    tileY - elevationHeight + tileHeight / 2,
                                    tileWidth, elevationHeight};

                if (elevationRect.Contains(mousePosition))
                {
                    hoveredCoordinate_ = {xCoordinate, yCoordinate};
                }

                for (auto i = 0; i < elevation; i++)
                {
                    tileY -= tileHeight / 4;
                }

                auto centerTop{
                    PointF{tileX + tileWidth / 2, tileY + tileHeight / 2}};

                auto dxTop{std::abs(mousePosition.x - centerTop.x) /
                           (tileWidth / 2)};
                auto dyTop{std::abs(mousePosition.y - centerTop.y) /
                           (tileHeight / 2)};
                if (dxTop + dyTop <= 1.0f)
                {
                    hoveredCoordinate_ = {xCoordinate, yCoordinate};
                }
            }
        }
    }
}