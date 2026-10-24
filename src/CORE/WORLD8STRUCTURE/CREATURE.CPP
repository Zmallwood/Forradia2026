//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CREATURE.HPP"
#include "CORE/CONFIGURATION/CREATURE8INDEX.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"

namespace FORRADIA8GAME {
    CREATURE::CREATURE(std::string_view typeName) {
        mType = HASH(typeName);
    }

    CREATURE::CREATURE(int type) {
        mType = type;

        auto typeName{_<CREATURE8INDEX>().GET8CREATURE8LABEL(type)};
    }

    void
    CREATURE::HIT(float damage, POINT8F hitPosition) {
        mHealth -= damage;

        mTicksLastHitOnSelf = NOW();

        mLastHitPosition = hitPosition;

        mTargetingPlayer = true;

        auto now{NOW()};

        if (now - mTicksLastHitOnOther > INVERT8SPEED(mAttackSpeed))
            mTicksLastHitOnOther = now;

        auto creatureLabel{_<CREATURE8INDEX>().GET8CREATURE8LABEL(mType)};

        std::stringstream ssDamage;

        ssDamage << std::fixed << std::setprecision(1) << damage;

        _<GUI8TEXT8CONSOLE>().PRINT8LINE("You hit a " + creatureLabel +
                                         " for " + ssDamage.str() + " damage.");
    }

    bool
    CREATURE::IS8DEAD() {
        return mHealth <= 0.0F;
    }
}