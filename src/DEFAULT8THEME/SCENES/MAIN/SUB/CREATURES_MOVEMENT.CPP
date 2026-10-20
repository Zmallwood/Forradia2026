//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "CREATURES_MOVEMENT.HPP"

void
CreaturesMovement::Update()
{
    auto worldArea{_<WORLD>().currentWorldArea_};

    auto playerPosition{_<PLAYER>().position_};

    auto now{NOW()};

    auto &creatures{worldArea->creaturesMirror_};

    for (auto it = creatures.begin(); it != creatures.end();)
    {
        auto creature{it->first};
        auto position{it->second};

        if (now > creature->ticksLastMovement_ +
                      INVERT8SPEED(creature->movementSpeed_))
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

            auto newPosition{position + POINT{dx, dy}};

            if (!worldArea->IS8VALID8COORDINATE(newPosition))
            {
                ++it;

                continue;
            }

            if (newPosition.x == static_cast<int>(playerPosition.x) &&
                newPosition.y == static_cast<int>(playerPosition.y))
            {
                ++it;

                continue;
            }

            auto newTile{worldArea->GET8TILE(newPosition)};

            if (newTile->ground_ == HASH("GroundWater") || newTile->creature_)
            {
                ++it;

                continue;
            }

            if (creature->type_ == HASH("CreatureDeer") ||
                creature->type_ == HASH("CreatureBoar"))
            {
                if (newTile->ground_ == HASH("GroundRock"))
                {
                    ++it;

                    continue;
                }
            }

            auto oldTile{worldArea->GET8TILE(position)};

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