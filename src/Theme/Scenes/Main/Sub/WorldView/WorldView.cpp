/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "WorldView.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "Theme/Scenes/Main/Sub/TileHovering.hpp"


namespace Forradia
{
    void WorldView::Render()
    {
        _<SDLDevice>().Clip(0.0f, 0.0f, 0.5f, 1.0f);

        auto viewWidth{GameProperties::k_viewWidth_};

        _<ColorRenderer>().FillRect(0.0f, 0.0f, viewWidth, 1.0f,
                                    Colors::k_black);

        auto worldArea{_<World>().currentWorldArea_};

        auto playerTile{worldArea->GetTile(_<Player>().position_)};

        auto playerElevation{0};

        if (playerTile)
        {
            playerElevation = playerTile->elevation_;
        }

        auto hoveredCoordinate{_<TileHovering>().hoveredCoordinate_};

        auto facedTile{_<Player>().facedTile_};

        auto tileWidth{_<GameProperties>().k_tileWidth_};
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

                auto numBlockingObjects{0};

                auto dx{_<Player>().position_.x - xCoordinate};
                auto dy{_<Player>().position_.y - yCoordinate};

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
                            if (!_<ObjectIndex>().IsSmallObject(
                                    object.second->type_))
                            {
                                numBlockingObjects++;

                                break;
                            }
                        }

                        currentXf += stepX;
                        currentYf += stepY;
                    }

                    if (numBlockingObjects >= 2)
                    {
                        continue;
                    }
                }

                auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                auto elevation{tile->elevation_};

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
                           y * tileWidth / 2};

                auto tileY{0.5f - 5.5f * tileHeight + x * tileHeight / 2 +
                           y * tileHeight / 2 +
                           playerElevation * tileHeight / 4};

                for (auto i = 0; i < elevation; i++)
                {
                    _<ImageRenderer>().DrawImage("Elevation", tileX,
                                                 tileY + tileHeight / 4,
                                                 tileWidth, tileHeight * 3 / 4);

                    tileY -= tileHeight / 4;
                }

                auto ground{tile->ground_};

                if (ground == Hash("GroundWater"))
                {
                    auto waterAnimIndex{
                        ((Now() + 10 * xCoordinate * yCoordinate) % 900) / 300};

                    std::string groundImageName{"GroundWater_" +
                                                std::to_string(waterAnimIndex)};

                    ground = Hash(groundImageName);
                }

                _<ImageRenderer>().DrawImage(ground, tileX, tileY,
                                             tileWidth + k_smallValue,
                                             tileHeight + k_smallValue);

                if (elevation > elevationNorth)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeNorth", tileX,
                                                 tileY, tileWidth, tileHeight);
                }

                if (elevation > elevationEast)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeEast", tileX,
                                                 tileY, tileWidth, tileHeight);
                }

                if (elevation > elevationSouth)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeSouth", tileX,
                                                 tileY, tileWidth, tileHeight);
                }

                if (elevation > elevationWest)
                {
                    _<ImageRenderer>().DrawImage("ElevationEdgeWest", tileX,
                                                 tileY, tileWidth, tileHeight);
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

                    auto isSmallObject{
                        _<ObjectIndex>().IsSmallObject(objectType)};

                    if (isSmallObject)
                    {
                        continue;
                    }

                    auto imageSize{_<ImageBank>().GetImageSize(objectType)};

                    auto objectWidth{imageSize.width / 60.0f * tileWidth};
                    auto objectHeight{imageSize.height / 60.0f * tileHeight};

                    auto objectX{tileX + tileWidth / 2 - objectWidth / 2};
                    auto objectY{tileY + tileHeight / 2 - objectHeight};

                    _<ImageRenderer>().DrawImage(objectType, objectX, objectY,
                                                 objectWidth, objectHeight);
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

                    _<ImageRenderer>().DrawImage(creatureType, creatureX,
                                                 creatureY, creatureWidth,
                                                 creatureHeight);
                }

                if (xCoordinate == _<Player>().position_.x &&
                    yCoordinate == _<Player>().position_.y)
                {
                    _<ImageRenderer>().DrawImage("Player", tileX,
                                                 tileY - tileHeight / 2,
                                                 tileWidth, tileHeight);
                }
            }
        }
        _<SDLDevice>().ResetClip();
    }
}