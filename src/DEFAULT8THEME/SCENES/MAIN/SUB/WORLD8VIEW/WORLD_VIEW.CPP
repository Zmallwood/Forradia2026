// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/COLORS/COLOR8RENDERER.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"
#include "CORE/SDL_DEVICE/SDL_DEVICE.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/NPC.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE_OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/SUB/TILE_HOVERING.HPP"
#include "WORLD_VIEW.HPP"

void WorldView::Render()
{
    _<SDLDevice>().Clip(0.0f, 0.0f, 0.5f, 1.0f);

    auto viewWidth = GAME8PROPERTIES::kViewWidth_;

    _<COLOR8RENDERER>().FILL8RECT(0.0f, 0.0f, viewWidth, 1.0f, COLORS::kBlack);

    auto worldArea = _<World>().currentWorldArea_;

    POINT playerPosition = {static_cast<int>(_<PLAYER>().position_.x),
                            static_cast<int>(_<PLAYER>().position_.y)};

    auto playerXInt = static_cast<int>(_<PLAYER>().position_.x);
    auto playerYInt = static_cast<int>(_<PLAYER>().position_.y);

    auto playerMoveDx = _<PLAYER>().position_.x - playerPosition.x;
    auto playerMoveDy = _<PLAYER>().position_.y - playerPosition.y;

    auto playerTile = worldArea->GetTile(playerPosition);

    auto playerElevation = 0;

    if (playerTile)
    {
        playerElevation = playerTile->elevation_;
    }

    auto hoveredCoordinate = _<TileHovering>().hoveredCoordinate_;

    auto facedTile = _<PLAYER>().facedTileCoordinate_;

    auto tileWidth = _<GAME8PROPERTIES>().kTileWidth_;
    auto tileHeight = CONVERT8WIDTH8TO8HEIGHT(tileWidth);

    auto tileGridSize = GAME8PROPERTIES::kTileGridSize_;

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

            POINT coordinateNorth = {xCoordinate, yCoordinate - 1};
            POINT coordinateEast = {xCoordinate + 1, yCoordinate};
            POINT coordinateSouth = {xCoordinate, yCoordinate + 1};
            POINT coordinateWest = {xCoordinate - 1, yCoordinate};

            POINT coordinateNorthEast = {xCoordinate + 1, yCoordinate - 1};
            POINT coordinateSouthEast = {xCoordinate + 1, yCoordinate + 1};
            POINT coordinateSouthWest = {xCoordinate - 1, yCoordinate + 1};
            POINT coordinateNorthWest = {xCoordinate - 1, yCoordinate - 1};

            auto elevationNorth = elevation;
            auto elevationEast = elevation;
            auto elevationSouth = elevation;
            auto elevationWest = elevation;

            auto elevationNorthEast = elevation;
            auto elevationSouthEast = elevation;
            auto elevationSouthWest = elevation;
            auto elevationNorthWest = elevation;

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

            if (worldArea->IsValidCoordinate(coordinateNorthEast))
            {
                elevationNorthEast =
                    worldArea->GetTile(coordinateNorthEast)->elevation_;
            }

            if (worldArea->IsValidCoordinate(coordinateSouthEast))
            {
                elevationSouthEast =
                    worldArea->GetTile(coordinateSouthEast)->elevation_;
            }

            if (worldArea->IsValidCoordinate(coordinateSouthWest))
            {
                elevationSouthWest =
                    worldArea->GetTile(coordinateSouthWest)->elevation_;
            }

            if (worldArea->IsValidCoordinate(coordinateNorthWest))
            {
                elevationNorthWest =
                    worldArea->GetTile(coordinateNorthWest)->elevation_;
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
                if (ground == HASH("GroundRock"))
                {
                    _<ImageRenderer>().DrawImage("ElevationRock", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }
                else if (ground == HASH("GroundWater"))
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

                if (i >= elevationNorth && i >= elevationNorthEast &&
                    i >= elevationEast)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeRight", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }

                if (i >= elevationSouth && i >= elevationSouthWest &&
                    i >= elevationWest)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeLeft", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }

                if (i >= elevationSouth && i >= elevationEast)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeMiddle", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);
                }

                tileY -= tileHeight / 4;
            }

            if (ground == HASH("GroundWater"))
            {
                auto waterAnimIndex =
                    ((NOW() + 10 * xCoordinate * yCoordinate) % 900) / 300;

                std::string groundImageName =
                    "GroundWater_" + std::to_string(waterAnimIndex);

                ground = HASH(groundImageName);
            }

            if (ground == HASH("GroundGrass"))
            {
                auto grassIndex =
                    ((10 * xCoordinate * yCoordinate) % 900) / 300;

                std::string groundImageName =
                    "GroundGrass_" + std::to_string(grassIndex);

                ground = HASH(groundImageName);
            }

            _<ImageRenderer>().DrawImage(ground, tileX, tileY,
                                         tileWidth + kSmallValue,
                                         tileHeight + kSmallValue);

            if (elevation != elevationNorth)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeNorth", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (elevation != elevationEast)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeEast", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (elevation != elevationSouth)
            {
                _<ImageRenderer>().DrawImage("ElevationEdgeSouth", tileX, tileY,
                                             tileWidth, tileHeight);
            }

            if (elevation != elevationWest)
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
                    _<OBJECT8INDEX>().GET8WORLD8VIEW8OBJECT8TYPE(objectType)};

                auto usedObjectType{objectType};

                if (worldViewObjectType != 0)
                {
                    usedObjectType = worldViewObjectType;
                }

                auto isSmallObject{
                    _<OBJECT8INDEX>().IS8SMALL8OBJECT(usedObjectType)};

                if (isSmallObject)
                {
                    continue;
                }

                auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(usedObjectType)};

                auto objectWidth{imageSize.width / 60.0f * tileWidth};
                auto objectHeight{imageSize.height / 60.0f * tileHeight};

                auto renderOffset{
                    _<OBJECT8INDEX>().GET8WORLD8VIEW8RENDER8OFFSET(objectType)};

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

                auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(npcType)};

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

                auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType)};

                auto creatureWidth{imageSize.width / 60.0f * tileWidth};
                auto creatureHeight{imageSize.height / 60.0f * tileHeight};

                auto creatureX{tileX + tileWidth / 2 - creatureWidth / 2};
                auto creatureY{tileY + tileHeight / 2 - creatureHeight};

                _<ImageRenderer>().DrawImage(creatureType, creatureX, creatureY,
                                             creatureWidth, creatureHeight);
            }

            if (xCoordinate == static_cast<int>(_<PLAYER>().position_.x) &&
                yCoordinate == static_cast<int>(_<PLAYER>().position_.y))
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
