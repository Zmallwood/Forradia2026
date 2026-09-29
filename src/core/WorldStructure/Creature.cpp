/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Creature.hpp"
#include "Core/Configuration/CreatureIndex.hpp"
#include "Core/GUICore/GUITextConsole.hpp"

namespace Forradia
{
    Creature::Creature(std::string_view typeName)
    {
        type_ = Hash(typeName);

        corpesType_ = Hash("Object" + std::string(typeName) + "Corpse");
    }

    void Creature::Hit(float damage, PointF hitPosition)
    {
        health_ -= damage;

        ticksLastHitOnSelf_ = Now();

        lastHitPosition_ = hitPosition;

        auto creatureLabel = _<CreatureIndex>().GetCreatureLabel(type_);

        std::stringstream ssDamage;
        ssDamage << std::fixed << std::setprecision(1) << damage;

        _<GUITextConsole>().PrintLine("You hit a " + creatureLabel + " for " +
                                      ssDamage.str() + " damage.");
    }

    bool Creature::IsDead()
    {
        return health_ <= 0.0f;
    }
}