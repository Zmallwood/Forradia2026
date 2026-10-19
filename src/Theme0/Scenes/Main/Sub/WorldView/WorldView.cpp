// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "WorldView.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/NPC.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "Theme0/Scenes/Main/Sub/TileHovering.hpp"

void WorldView::Render()
{
    _<SDLDevice>().Clip(0.0f, 0.0f, 0.5f, 1.0f);

    auto viewWidth = GameProperties::k_viewWidth_;

    _<ColorRenderer>().FillRect(0.0f, 0.0f, viewWidth, 1.0f, Colors::k_black);

    auto worldArea = _<World>().currentWorldArea_;

    Point playerPosition = {static_cast<int>(_<Player>().position_.x),
                            static_cast<int>(_<Player>().position_.y)};

    auto playerXInt = static_cast<int>(_<Player>().position_.x);
    auto playerYInt = static_cast<int>(_<Player>().position_.y);

    auto playerMoveDx = _<Player>().position_.x - playerPosition.x;
    auto playerMoveDy = _<Player>().position_.y - playerPosition.y;

    auto playerTile = worldArea->GetTile(playerPosition);

    auto playerElevation = 0;

    if (playerTile)
    {
        playerElevation = playerTile->elevation_;
    }

    auto hoveredCoordinate = _<TileHovering>().hoveredCoordinate_;

    auto facedTile = _<Player>().facedTileCoordinate_;

    auto tileWidth = _<GameProperties>().k_tileWidth_;
    auto tileHeight = ConvertWidthToHeight(tileWidth);

    auto tileGridSize = GameProperties::k_tileGridSize_;

    auto numGridRows = tileGridSize - 11;
    auto numGridColumns = tileGridSize - 11;

    auto playerLoopX = 5;
    auto playerLoopY = 5;

    for (auto y = -numGridRows; y < 11 + numGridRows; y++)
    {
        for (auto x = -numGridColumns; x < 11 + numGridColumns; x++)
        {
            auto xCoordinate = playerPosition.x - 5 + x;
            auto yCoordinate = playerPosition.y - 5 + y;

            if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
            {
                continue;
            }

            auto tile = worldArea->GetTile(xCoordinate, yCoordinate);

            auto elevation = tile->elevation_;

            Point coordinateNorth = {xCoordinate, yCoordinate - 1};
            Point coordinateEast = {xCoordinate + 1, yCoordinate};
            Point coordinateSouth = {xCoordinate, yCoordinate + 1};
            Point coordinateWest = {xCoordinate - 1, yCoordinate};

            auto elevationNorth = elevation;
            auto elevationEast = elevation;
            auto elevationSouth = elevation;
            auto elevationWest = elevation;

            if (worldArea->IsValidCoordinate(coordinateNorth))
            {
                elevationNorth =
                    worldArea->GetTile(coordinateNorth)->elevation_;
            }

            if (worldArea->IsValidCoordinate(coordinateEast))
            {
                elevationEast = worldArea->GetTile(coordinateEast)->elevation_;
            }

            if (worldArea->IsValidCoordinate(coordinateSouth))
            {
                elevationSouth =
                    worldArea->GetTile(coordinateSouth)->elevation_;
            }

            if (worldArea->IsValidCoordinate(coordinateWest))
            {
                elevationWest = worldArea->GetTile(coordinateWest)->elevation_;
            }

            auto tileX = 0.25f - tileWidth / 2 + x * tileWidth / 2 -
                         y * tileWidth / 2 - playerMoveDx * tileWidth / 2 +
                         playerMoveDy * tileWidth / 2;

            auto tileYOriginal =
                0.5f - 5.5f * tileHeight + x * tileHeight / 2 +
                y * tileHeight / 2 + playerElevation * tileHeight / 4 -
                playerMoveDx * tileHeight / 2 - playerMoveDy * tileHeight / 2;

            auto tileY = tileYOriginal;

            tileY = tileYOriginal;

            auto ground = tile->ground_;

            for (auto i = 0; i < elevation; i++)
            {
                if (ground == Hash("GroundRock"))
                {
                    _<ImageRenderer>().DrawImage("ElevationRock", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }
                else if (ground == Hash("GroundWater"))
                {
                    _<ImageRenderer>().DrawImage("ElevationWater", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }
                else
                {
                    _<ImageRenderer>().DrawImage("Elevation", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }

                tileY -= tileHeight / 4;
            }

            if (ground == Hash("GroundWater"))
            {
                auto waterAnimIndex =
                    ((Now() + 10 * xCoordinate * yCoordinate) % 900) / 300;

                std::string groundImageName =
                    "GroundWater_" + std::to_string(waterAnimIndex);

                ground = Hash(groundImageName);
            }

            if (ground == Hash("GroundGrass"))
            {
                auto grassIndex =
                    ((10 * xCoordinate * yCoordinate) % 900) / 300;

                std::string groundImageName =
                    "GroundGrass_" + std::to_string(grassIndex);

                ground = Hash(groundImageName);
            }

            _<ImageRenderer>().DrawImage(ground, tileX, tileY,
                                         tileWidth + k_smallValue,
                                         tileHeight + k_smallValue);

            if (elevation > elevationNorth)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeNorth", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (elevation > elevationEast)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeEast", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (elevation > elevationSouth)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeSouth", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (elevation > elevationWest)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeWest", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (xCoordinate == facedTile.x && yCoordinate == facedTile.y)
            {
                _<ImageRenderer>().DrawImage("FacedTile", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (xCoordinate == hoveredCoordinate.x &&
                yCoordinate == hoveredCoordinate.y)
            {

                _<ImageRenderer>().DrawImage("HoveredTile", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            auto objects{tile->tileObjects_->objects_};

            for (auto entry : objects)
            {
                auto object{entry.second};

                auto objectType{object->type_};

                auto worldViewObjectType{
                    _<ObjectIndex>().GetWorldViewObjectType(objectType)};

                auto usedObjectType{objectType};

                if (worldViewObjectType != 0)
                {
                    usedObjectType = worldViewObjectType;
                }

                auto isSmallObject{
                    _<ObjectIndex>().IsSmallObject(usedObjectType)};

                if (isSmallObject)
                {
                    continue;
                }

                auto imageSize{_<ImageBank>().GetImageSize(usedObjectType)};

                auto objectWidth{imageSize.width / 60.0f * tileWidth};
                auto objectHeight{imageSize.height / 60.0f * tileHeight};

                auto renderOffset{
                    _<ObjectIndex>().GetWorldViewRenderOffset(objectType)};

                auto objectX{tileX + tileWidth / 2 - objectWidth / 2 +
                             renderOffset.x * tileWidth};
                auto objectY{tileY + tileHeight / 2 - objectHeight +
                             renderOffset.y * tileHeight};

                _<ImageRenderer>().DrawImage(usedObjectType, objectX, objectY,
                                             objectWidth, objectHeight);
            }

            auto tileYCopy = tileYOriginal;

            auto npc{tile->npc_};

            if (npc)
            {
                auto npcType{npc->type_};

                auto imageSize{_<ImageBank>().GetImageSize(npcType)};

                auto npcWidth{imageSize.width / 60.0f * tileWidth};
                auto npcHeight{imageSize.height / 60.0f * tileHeight};

                auto npcX{tileX + tileWidth / 2 - npcWidth / 2};
                auto npcY{tileY + tileHeight / 2 - npcHeight};

                _<ImageRenderer>().DrawImage(npcType, npcX, npcY, npcWidth,
                                             npcHeight);
            }

            auto creature{tile->creature_};

            if (creature)
            {
                auto creatureType{creature->type_};

                auto imageSize{_<ImageBank>().GetImageSize(creatureType)};

                auto creatureWidth{imageSize.width / 60.0f * tileWidth};
                auto creatureHeight{imageSize.height / 60.0f * tileHeight};

                auto creatureX{tileX + tileWidth / 2 - creatureWidth / 2};
                auto creatureY{tileY + tileHeight / 2 - creatureHeight};

                _<ImageRenderer>().DrawImage(creatureType, creatureX, creatureY,
                                             creatureWidth, creatureHeight);
            }

            if (xCoordinate == static_cast<int>(_<Player>().position_.x) &&
                yCoordinate == static_cast<int>(_<Player>().position_.y))
            {
                auto tileXPlayer{0.25f - tileWidth / 2 + 5 * tileWidth / 2 -
                                 5 * tileWidth / 2};

                auto tileYPlayer{0.5f - 5.5f * tileHeight + 5 * tileHeight / 2 +
                                 5 * tileHeight / 2};

                _<ImageRenderer>().DrawImage("Player", tileXPlayer,
                                             tileYPlayer - tileHeight,
                                             tileWidth, tileHeight);
            }
        }
    }

    _<SDLDevice>().ResetClip();
}
