/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Creature.hpp"

namespace Forradia
{
    Creature::Creature(std::string_view typeName)
    {
        type_ = Hash(typeName);

        corpesType_ = Hash(std::string(typeName) + "Corpse");
    }

    void Creature::Hit(float damage, PointF hitPosition)
    {
        health_ -= damage;

        ticksLastHitOnSelf_ = Now();

        lastHitPosition_ = hitPosition;
    }

    bool Creature::IsDead()
    {
        return health_ <= 0.0f;
    }
}