//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CREATURE_RESPAWNER.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"

namespace FORRADIA
{
    void
    CreatureRespawner::Update()
    {
        auto now{NOW()};

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto size{worldArea->GET8SIZE()};

        for (auto it = creatureRespawns_.begin();
             it != creatureRespawns_.end();)
        {
            auto creatureRespawnTime{it->first};
            auto creatureType{it->second};

            if (now >= creatureRespawnTime)
            {
                auto newCreature{std::make_shared<CREATURE>(creatureType)};

                int x;
                int y;
                std::shared_ptr<TILE> tile;

                do
                {
                    x = rand() % size.width;
                    y = rand() % size.height;

                    tile = worldArea->GET8TILE({x, y});
                } while (tile->ground_ == HASH("GroundWater") ||
                         tile->ground_ == HASH("GroundDirt"));

                if (tile)
                {
                    tile->creature_ = newCreature;

                    worldArea->creaturesMirror_.insert({newCreature, {x, y}});
                }

                creatureRespawns_.erase(it++);

                continue;
            }

            ++it;
        }
    }

    void
    CreatureRespawner::RespawnCreature(int creatureType, int respawnTimeMillis)
    {
        auto creatureRespawnTime{NOW() + respawnTimeMillis};

        creatureRespawns_.insert({creatureRespawnTime, creatureType});
    }
}