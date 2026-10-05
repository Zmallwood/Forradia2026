// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CreatureRespawner.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

void CreatureRespawner::Update()
{
    auto now{Now()};

    auto worldArea{_<World>().currentWorldArea_};

    auto size{worldArea->GetSize()};

    for (auto it = creatureRespawns_.begin(); it != creatureRespawns_.end();)
    {
        auto creatureRespawnTime{it->first};
        auto creatureType{it->second};

        if (now >= creatureRespawnTime)
        {
            auto newCreature{std::make_shared<Creature>(creatureType)};

            int x;
            int y;
            std::shared_ptr<Tile> tile;

            do
            {
                x = rand() % size.width;
                y = rand() % size.height;

                tile = worldArea->GetTile({x, y});
            } while (tile->ground_ == Hash("GroundWater") ||
                     tile->ground_ == Hash("GroundDirt"));

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

void CreatureRespawner::RespawnCreature(int creatureType, int respawnTimeMillis)
{
    auto creatureRespawnTime{Now() + respawnTimeMillis};

    creatureRespawns_.insert({creatureRespawnTime, creatureType});
}