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
    }

    void Creature::Hit(int damage, PointF hitPosition)
    {
        ticksLastHitReceive_ = Now();

        lastHitPosition_ = hitPosition;
    }
}