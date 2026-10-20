// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/WORLD_STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD_STRUCTURE/WORLD.HPP"
#include "CORE/WORLD_STRUCTURE/WORLD_AREA.HPP"
#include "CREATURES_COMBAT_TO_PLAYER.HPP"

void CreaturesCombatToPlayer::Update()
{
    auto now{NOW()};

    auto playerPosition{_<Player>().position_};

    auto worldArea{_<World>().currentWorldArea_};

    auto &creatures{worldArea->creaturesMirror_};

    for (auto entry : creatures)
    {
        auto creature{entry.first};
        auto position{entry.second};

        if (creature->targetingPlayer_)
        {
            auto dx{position.x - static_cast<int>(playerPosition.x)};
            auto dy{position.y - static_cast<int>(playerPosition.y)};

            auto absDx{std::abs(dx)};
            auto absDy{std::abs(dy)};

            if ((absDx <= 1 && absDy == 0) || (absDx == 0 && absDy <= 1))
            {
                if (now > creature->ticksLastHitOnOther_ +
                              INVERT8SPEED(creature->attackSpeed_))
                {
                    _<Player>().Hit(1.0f);

                    creature->ticksLastHitOnOther_ = now;
                }
            }
        }
    }
}