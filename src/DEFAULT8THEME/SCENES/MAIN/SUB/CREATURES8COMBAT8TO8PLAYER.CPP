//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CREATURES8COMBAT8TO8PLAYER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"

namespace FORRADIA8GAME {
    void
    CREATURES8COMBAT8TO8PLAYER::UPDATE() {
        auto now{NOW()};

        auto playerPosition{_<PLAYER>().mPosition};

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto &creatures{worldArea->creaturesMirror_};

        for (auto entry : creatures) {
            auto creature{entry.first};
            auto position{entry.second};

            if (creature->targetingPlayer_) {
                auto dx{position.x - static_cast<int>(playerPosition.x)};
                auto dy{position.y - static_cast<int>(playerPosition.y)};

                auto absDx{std::abs(dx)};
                auto absDy{std::abs(dy)};

                if ((absDx <= 1 && absDy == 0) || (absDx == 0 && absDy <= 1)) {
                    if (now > creature->ticksLastHitOnOther_ +
                                  INVERT8SPEED(creature->attackSpeed_)) {
                        _<PLAYER>().HIT(1.0F);

                        creature->ticksLastHitOnOther_ = now;
                    }
                }
            }
        }
    }
}