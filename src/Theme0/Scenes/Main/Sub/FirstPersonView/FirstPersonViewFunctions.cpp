/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "FirstPersonViewFunctions.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    std::map<std::pair<int, int>, PositionedObject> GetOrderedObjects()
    {
        auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};

        auto worldArea{_<World>().currentWorldArea_};
        auto facedTile{worldArea->GetTile(_<Player>().facedTileCoordinate_)};

        if (!facedTile)
        {
            return {};
        }

        auto objects{facedTile->tileObjects_->objects_};

        std::map<std::pair<int, int>, PositionedObject> orderedObjects;

        for (auto entry : objects)
        {
            auto position{entry.first};
            auto object{entry.second};

            int xPos;
            int yPos;

            auto facingDirection{_<Player>().facingDirection_};

            switch (facingDirection)
            {
            case WorldDirections::North:
                xPos = position.x;
                yPos = position.y;
                break;
            case WorldDirections::East:
                xPos = position.y;
                yPos = tileUnitsWidth - 1 - position.x;
                break;
            case WorldDirections::South:
                xPos = tileUnitsWidth - 1 - position.x;
                yPos = tileUnitsWidth - 1 - position.y;
                break;
            case WorldDirections::West:
                xPos = tileUnitsWidth - 1 - position.y;
                yPos = position.x;
                break;
            }

            PositionedObject positionedObject;
            positionedObject.position_ = {xPos, yPos};
            positionedObject.object_ = object;

            orderedObjects[{yPos, xPos}] = positionedObject;
        }

        return orderedObjects;
    }

    Point GetHoveredTilePosition(PointF mouseOffset)
    {
        constexpr auto k_margin{GameProperties::k_firstPersonViewMargin_};
        auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};
        auto viewWidth{GameProperties::k_viewWidth_};

        auto hoveredTilePosition = Point{-1, -1};

        auto anchorPosition{GetMousePosition() - mouseOffset};

        auto groundTop{0.75f + k_margin.y};
        auto groundHeight{0.25f - 2 * k_margin.y};

        auto relativeY{(anchorPosition.y - groundTop) / groundHeight};

        if (relativeY >= 0.0f && relativeY <= 1.0f)
        {
            // Bases sit on the near edge of a cell, so step just inside it.
            auto hoveredY{static_cast<int>(relativeY * tileUnitsWidth - 0.001f)};

            if (hoveredY < 0)
            {
                hoveredY = 0;
            }

            if (hoveredY >= tileUnitsWidth)
            {
                hoveredY = tileUnitsWidth - 1;
            }

            auto tileWidth{viewWidth - 2 * k_margin.x -
                           static_cast<float>(tileUnitsWidth - hoveredY) /
                               tileUnitsWidth * viewWidth * 0.6f};

            auto tileLeft{1.0f - viewWidth + k_margin.x +
                          static_cast<float>(tileUnitsWidth - hoveredY) /
                              tileUnitsWidth * viewWidth * 0.3f};

            auto relativeX{(anchorPosition.x - tileLeft) / tileWidth};

            if (relativeX >= 0.0f && relativeX < 1.0f)
            {
                auto hoveredX{static_cast<int>(relativeX * tileUnitsWidth)};

                if (hoveredX >= tileUnitsWidth)
                {
                    hoveredX = tileUnitsWidth - 1;
                }

                int tileX{hoveredX};
                int tileY{hoveredY};

                switch (_<Player>().facingDirection_)
                {
                case WorldDirections::North:
                    break;
                case WorldDirections::East:
                    tileX = tileUnitsWidth - 1 - hoveredY;
                    tileY = hoveredX;
                    break;
                case WorldDirections::South:
                    tileX = tileUnitsWidth - 1 - hoveredX;
                    tileY = tileUnitsWidth - 1 - hoveredY;
                    break;
                case WorldDirections::West:
                    tileX = hoveredY;
                    tileY = tileUnitsWidth - 1 - hoveredX;
                    break;
                }

                hoveredTilePosition = {tileX, tileY};
            }
        }

        return hoveredTilePosition;
    }
}