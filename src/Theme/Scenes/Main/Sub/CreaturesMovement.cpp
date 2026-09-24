/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "CreaturesMovement.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/CoreGameObjects/Player.hpp"

namespace Forradia
{
    void CreaturesMovement::Update()
    {
        auto worldArea{_<World>().currentWorldArea_};

        auto playerPosition{_<Player>().position_};

        auto now{Now()};

        auto &creatures{worldArea->creaturesMirror_};

        for (auto it = creatures.begin(); it != creatures.end();)
        {
            auto creature{it->first};
            auto position{it->second};

            if (now > creature->ticksLastMovement_ +
                          InvertSpeed(creature->movementSpeed_))
            {
                auto direction{rand() % 4};

                auto dx{0};
                auto dy{0};

                switch (direction)
                {
                case 0:
                    dy = -1;
                    break;
                case 1:
                    dx = 1;
                    break;
                case 2:
                    dy = 1;
                    break;
                case 3:
                    dx = -1;
                    break;
                }

                auto newPosition{position + Point{dx, dy}};

                if (!worldArea->IsValidCoordinate(newPosition))
                {
                    ++it;

                    continue;
                }

                if (newPosition == playerPosition)
                {
                    ++it;

                    continue;
                }

                auto newTile{worldArea->GetTile(newPosition)};

                if (newTile->ground_ == Hash("GroundWater") ||
                    newTile->creature_)
                {
                    ++it;

                    continue;
                }

                auto oldTile{worldArea->GetTile(position)};

                newTile->creature_ = creature;
                oldTile->creature_ = nullptr;
                
                creatures.erase(it++);
                creatures.insert({creature, newPosition});

                creature->ticksLastMovement_ = now;

                continue;
            }

            ++it;
        }
    }
}