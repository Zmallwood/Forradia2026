/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "CreaturesCombatToPlayer.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

void CreaturesCombatToPlayer::Update()
{
    auto now{Now()};

    auto playerPosition{_<Player>().position_};

    auto worldArea{_<World>().currentWorldArea_};

    auto &creatures{worldArea->creaturesMirror_};

    for (auto entry : creatures)
    {
        auto creature{entry.first};
        auto position{entry.second};

        if (creature->targetingPlayer_)
        {
            auto dx{position.x - playerPosition.x};
            auto dy{position.y - playerPosition.y};

            auto absDx{std::abs(dx)};
            auto absDy{std::abs(dy)};

            if ((absDx <= 1 && absDy == 0) || (absDx == 0 && absDy <= 1))
            {
                if (now > creature->ticksLastHitOnOther_ +
                              InvertSpeed(creature->attackSpeed_))
                {
                    _<Player>().Hit(1.0f);

                    creature->ticksLastHitOnOther_ = now;
                }
            }
        }
    }
}