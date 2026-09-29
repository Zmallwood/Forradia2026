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
}