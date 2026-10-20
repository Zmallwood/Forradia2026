// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"
#include "TILE_HOVERING.HPP"

void TileHovering::Update()
{
    auto mousePosition{GET8MOUSE8POSITION()};

    auto worldArea{_<World>().currentWorldArea_};

    POINT playerPosition{static_cast<int>(_<PLAYER>().position_.x),
                         static_cast<int>(_<PLAYER>().position_.y)};

    auto playerMoveDx{_<PLAYER>().position_.x - playerPosition.x};
    auto playerMoveDy{_<PLAYER>().position_.y - playerPosition.y};

    auto playerTile{worldArea->GetTile(playerPosition)};

    if (!playerTile)
    {
        return;
    }

    auto playerElevation{playerTile->elevation_};

    auto tileWidth{GAME8PROPERTIES::kTileWidth_};
    auto tileHeight{CONVERT8WIDTH8TO8HEIGHT(tileWidth)};

    auto tileGridSize{GAME8PROPERTIES::kTileGridSize_};

    auto numGridRows{tileGridSize - 11};
    auto numGridColumns{tileGridSize - 11};

    // for (auto y = -6; y < 11 + 6; y++)
    // {
    //     for (auto x = -6; x < 11 + 6; x++)
    //     {
    for (auto y = -numGridRows; y < 11 + numGridRows; y++)
    {
        for (auto x = -numGridColumns; x < 11 + numGridColumns; x++)
        {
            auto xCoordinate{playerPosition.x - 5 + x};
            auto yCoordinate{playerPosition.y - 5 + y};

            if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
            {
                continue;
            }

            auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

            auto elevation{tile->elevation_};

            auto tileX{0.25f - tileWidth / 2 + x * tileWidth / 2 -
                       y * tileWidth / 2 - playerMoveDx * tileWidth / 2 +
                       playerMoveDy * tileWidth / 2};

            auto tileY{0.5f - 5.5f * tileHeight + x * tileHeight / 2 +
                       y * tileHeight / 2 + playerElevation * tileHeight / 4 -
                       playerMoveDx * tileHeight / 2 -
                       playerMoveDy * tileHeight / 2};

            auto centerBottom{
                POINT8F{tileX + tileWidth / 2, tileY + tileHeight / 2}};

            auto dxBottom{std::abs(mousePosition.x - centerBottom.x) /
                          (tileWidth / 2)};
            auto dyBottom{std::abs(mousePosition.y - centerBottom.y) /
                          (tileHeight / 2)};
            if (dxBottom + dyBottom <= 1.0f)
            {
                hoveredCoordinate_ = {xCoordinate, yCoordinate};
            }

            auto elevationHeight{elevation * tileHeight / 4};

            RECT8F elevationRect{tileX,
                                 tileY - elevationHeight + tileHeight / 2,
                                 tileWidth, elevationHeight};

            if (elevationRect.CONTAINS(mousePosition))
            {
                hoveredCoordinate_ = {xCoordinate, yCoordinate};
            }

            for (auto i = 0; i < elevation; i++)
            {
                tileY -= tileHeight / 4;
            }

            auto centerTop{
                POINT8F{tileX + tileWidth / 2, tileY + tileHeight / 2}};

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