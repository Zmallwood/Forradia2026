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

    auto viewWidth{GameProperties::k_viewWidth_};

    _<ColorRenderer>().FillRect(0.0f, 0.0f, viewWidth, 1.0f, Colors::k_black);

    auto worldArea{_<World>().currentWorldArea_};

    Point playerPosition{static_cast<int>(_<Player>().position_.x),
                         static_cast<int>(_<Player>().position_.y)};

    auto playerMoveDx{_<Player>().position_.x - playerPosition.x};
    auto playerMoveDy{_<Player>().position_.y - playerPosition.y};

    auto playerTile{worldArea->GetTile(playerPosition)};

    auto playerElevation{0};

    if (playerTile)
    {
        playerElevation = playerTile->elevation_;
    }

    auto hoveredCoordinate{_<TileHovering>().hoveredCoordinate_};

    auto facedTile{_<Player>().facedTileCoordinate_};

    auto tileWidth{_<GameProperties>().k_tileWidth_};
    auto tileHeight{ConvertWidthToHeight(tileWidth)};

    auto playerLoopX{5};
    auto playerLoopY{5};

    for (auto renderPass = 0; renderPass < 2; renderPass++)
    {
        // for (auto y = -6; y < 11 + 6; y++)
        // {
        //     for (auto x = -6; x < 11 + 6; x++)
        //     {
        auto maxZReached{false};

        for (auto z = 0; !maxZReached; z++)
        {
            maxZReached = true;

            for (auto y = -12; y < 11 + 12; y++)
            {
                for (auto x = -12; x < 11 + 12; x++)
                {
                    auto xCoordinate{playerPosition.x - 5 + x};
                    auto yCoordinate{playerPosition.y - 5 + y};

                    if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                    {
                        continue;
                    }

                    auto numBlockingObjects{0};

                    auto dx{playerPosition.x - xCoordinate};
                    auto dy{playerPosition.y - yCoordinate};

                    if (dx != 0 || dy != 0)
                    {
                        auto numSteps{std::max(std::abs(dx), std::abs(dy))};

                        auto stepX{static_cast<float>(dx) / numSteps};
                        auto stepY{static_cast<float>(dy) / numSteps};

                        auto currentXf{static_cast<float>(xCoordinate) + stepX};
                        auto currentYf{static_cast<float>(yCoordinate) + stepY};

                        for (auto i = 0; i < numSteps - 1; i++)
                        {
                            auto currentX{static_cast<int>(currentXf)};
                            auto currentY{static_cast<int>(currentYf)};

                            auto tile{worldArea->GetTile(currentX, currentY)};

                            if (!tile)
                            {
                                continue;
                            }

                            for (auto object : tile->tileObjects_->objects_)
                            {
                                if (_<ObjectIndex>().ObjectBlocksSight(
                                        object.second->type_))
                                {
                                    numBlockingObjects++;

                                    break;
                                }
                            }

                            currentXf += stepX;
                            currentYf += stepY;
                        }
                    }

                    auto sightBlocked{numBlockingObjects >= 2};

                    sightBlocked = false;

                    auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                    auto elevation{tile->elevation_};

                    if (z <= elevation)
                    {
                        maxZReached = false;
                    }
                    else
                    {
                        continue;
                    }

                    auto doDraw{true};
                    auto drawFromElevation{0};
                    auto drawUpToElevation{0};

                    if (renderPass == 0)
                    {
                        if (x + y <= playerLoopX + playerLoopY)
                        {
                            drawUpToElevation = elevation;
                        }
                        else
                        {
                            drawUpToElevation = playerElevation;
                        }
                    }
                    else if (renderPass == 1)
                    {
                        if (x + y <= playerLoopX + playerLoopY)
                        {
                            doDraw = false;
                        }
                        else
                        {
                            drawFromElevation = playerElevation + 1;
                            drawUpToElevation = elevation;
                        }
                    }

                    if (!doDraw)
                    {
                        continue;
                    }

                    Point coordinateNorth{xCoordinate, yCoordinate - 1};
                    Point coordinateEast{xCoordinate + 1, yCoordinate};
                    Point coordinateSouth{xCoordinate, yCoordinate + 1};
                    Point coordinateWest{xCoordinate - 1, yCoordinate};

                    auto elevationNorth{elevation};
                    auto elevationEast{elevation};
                    auto elevationSouth{elevation};
                    auto elevationWest{elevation};

                    if (worldArea->IsValidCoordinate(coordinateNorth))
                    {
                        elevationNorth =
                            worldArea->GetTile(coordinateNorth)->elevation_;
                    }

                    if (worldArea->IsValidCoordinate(coordinateEast))
                    {
                        elevationEast =
                            worldArea->GetTile(coordinateEast)->elevation_;
                    }

                    if (worldArea->IsValidCoordinate(coordinateSouth))
                    {
                        elevationSouth =
                            worldArea->GetTile(coordinateSouth)->elevation_;
                    }

                    if (worldArea->IsValidCoordinate(coordinateWest))
                    {
                        elevationWest =
                            worldArea->GetTile(coordinateWest)->elevation_;
                    }

                    auto tileX{0.25f - tileWidth / 2 + x * tileWidth / 2 -
                               y * tileWidth / 2 -
                               playerMoveDx * tileWidth / 2 +
                               playerMoveDy * tileWidth / 2};

                    auto tileYOriginal{0.5f - 5.5f * tileHeight +
                                       x * tileHeight / 2 + y * tileHeight / 2 +
                                       playerElevation * tileHeight / 4 -
                                       playerMoveDx * tileHeight / 2 -
                                       playerMoveDy * tileHeight / 2};

                    auto tileY{tileYOriginal};

                    if (sightBlocked)
                    {
                        for (auto i = 0; i < elevationWest; i++)
                        {
                            if (i == z)
                            {
                                _<ImageRenderer>().DrawImage(
                                    "ElevationWestBackSideBlack", tileX,
                                    tileY - tileHeight / 4, tileWidth,
                                    tileHeight * 3 / 4);
                            }

                            tileY -= tileHeight / 4;
                        }

                        tileY = tileYOriginal;

                        for (auto i = 0; i < elevationNorth; i++)
                        {
                            if (i == z)
                            {
                                _<ImageRenderer>().DrawImage(
                                    "ElevationNorthBackSideBlack", tileX,
                                    tileY - tileHeight / 4, tileWidth,
                                    tileHeight * 3 / 4);
                            }

                            tileY -= tileHeight / 4;
                        }

                        continue;
                    }

                    tileY = tileYOriginal;

                    auto ground{tile->ground_};

                    for (auto i = 0; i < elevation; i++)
                    {
                        if (i == z && i >= drawFromElevation && i <= drawUpToElevation)
                        {
                            if (ground == Hash("GroundRock"))
                            {
                                _<ImageRenderer>().DrawImage(
                                    "ElevationRock", tileX,
                                    tileY + tileHeight / 4, tileWidth,
                                    tileHeight * 3 / 4);
                            }
                            else if (ground == Hash("GroundWater"))
                            {
                                _<ImageRenderer>().DrawImage(
                                    "ElevationWater", tileX,
                                    tileY + tileHeight / 4, tileWidth,
                                    tileHeight * 3 / 4);
                            }
                            else
                            {
                                _<ImageRenderer>().DrawImage(
                                    "Elevation", tileX, tileY + tileHeight / 4,
                                    tileWidth, tileHeight * 3 / 4);
                            }
                        }

                        tileY -= tileHeight / 4;
                    }

                    if (elevation == z && z >= drawFromElevation &&
                        z <= drawUpToElevation)
                    {
                        if (ground == Hash("GroundWater"))
                        {
                            auto waterAnimIndex{
                                ((Now() + 10 * xCoordinate * yCoordinate) %
                                 900) /
                                300};

                            std::string groundImageName{
                                "GroundWater_" +
                                std::to_string(waterAnimIndex)};

                            ground = Hash(groundImageName);
                        }

                        _<ImageRenderer>().DrawImage(ground, tileX, tileY,
                                                     tileWidth + k_smallValue,
                                                     tileHeight + k_smallValue);

                        if (elevation > elevationNorth)
                        {
                            _<ImageRenderer>().DrawImage("ElevationEdgeNorth",
                                                         tileX, tileY,
                                                         tileWidth, tileHeight);
                        }

                        if (elevation > elevationEast)
                        {
                            _<ImageRenderer>().DrawImage("ElevationEdgeEast",
                                                         tileX, tileY,
                                                         tileWidth, tileHeight);
                        }

                        if (elevation > elevationSouth)
                        {
                            _<ImageRenderer>().DrawImage("ElevationEdgeSouth",
                                                         tileX, tileY,
                                                         tileWidth, tileHeight);
                        }

                        if (elevation > elevationWest)
                        {
                            _<ImageRenderer>().DrawImage("ElevationEdgeWest",
                                                         tileX, tileY,
                                                         tileWidth, tileHeight);
                        }

                        if (xCoordinate == facedTile.x &&
                            yCoordinate == facedTile.y)
                        {
                            _<ImageRenderer>().DrawImage("FacedTile", tileX,
                                                         tileY, tileWidth,
                                                         tileHeight);
                        }

                        if (xCoordinate == hoveredCoordinate.x &&
                            yCoordinate == hoveredCoordinate.y)
                        {

                            _<ImageRenderer>().DrawImage("HoveredTile", tileX,
                                                         tileY, tileWidth,
                                                         tileHeight);
                        }

                        auto objects{tile->tileObjects_->objects_};

                        for (auto entry : objects)
                        {
                            auto object{entry.second};

                            auto objectType{object->type_};

                            auto worldViewObjectType{
                                _<ObjectIndex>().GetWorldViewObjectType(
                                    objectType)};

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

                            auto imageSize{
                                _<ImageBank>().GetImageSize(usedObjectType)};

                            auto objectWidth{imageSize.width / 60.0f *
                                             tileWidth};
                            auto objectHeight{imageSize.height / 60.0f *
                                              tileHeight};

                            auto renderOffset{
                                _<ObjectIndex>().GetWorldViewRenderOffset(
                                    objectType)};

                            auto objectX{tileX + tileWidth / 2 -
                                         objectWidth / 2 +
                                         renderOffset.x * tileWidth};
                            auto objectY{tileY + tileHeight / 2 - objectHeight +
                                         renderOffset.y * tileHeight};

                            _<ImageRenderer>().DrawImage(
                                usedObjectType, objectX, objectY, objectWidth,
                                objectHeight);
                        }

                        auto npc{tile->npc_};

                        if (npc)
                        {
                            auto npcType{npc->type_};

                            auto imageSize{
                                _<ImageBank>().GetImageSize(npcType)};

                            auto npcWidth{imageSize.width / 60.0f * tileWidth};
                            auto npcHeight{imageSize.height / 60.0f *
                                           tileHeight};

                            auto npcX{tileX + tileWidth / 2 - npcWidth / 2};
                            auto npcY{tileY + tileHeight / 2 - npcHeight};

                            _<ImageRenderer>().DrawImage(npcType, npcX, npcY,
                                                         npcWidth, npcHeight);
                        }

                        auto creature{tile->creature_};

                        if (creature)
                        {
                            auto creatureType{creature->type_};

                            auto imageSize{
                                _<ImageBank>().GetImageSize(creatureType)};

                            auto creatureWidth{imageSize.width / 60.0f *
                                               tileWidth};
                            auto creatureHeight{imageSize.height / 60.0f *
                                                tileHeight};

                            auto creatureX{tileX + tileWidth / 2 -
                                           creatureWidth / 2};
                            auto creatureY{tileY + tileHeight / 2 -
                                           creatureHeight};

                            _<ImageRenderer>().DrawImage(
                                creatureType, creatureX, creatureY,
                                creatureWidth, creatureHeight);
                        }
                    }
                }
            }
        }

        if (renderPass == 0)
        {
            auto tileXPlayer{0.25f - tileWidth / 2 + 5 * tileWidth / 2 -
                             5 * tileWidth / 2};

            auto tileYPlayer{0.5f - 5.5f * tileHeight + 5 * tileHeight / 2 +
                             5 * tileHeight / 2};

            _<ImageRenderer>().DrawImage("Player", tileXPlayer,
                                         tileYPlayer - tileHeight, tileWidth,
                                         tileHeight);
        }
    }

    _<SDLDevice>().ResetClip();
}
