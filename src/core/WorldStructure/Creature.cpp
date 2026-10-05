// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "Creature.hpp"
#include "Core/Configuration/CreatureIndex.hpp"
#include "Core/GUICore/GUITextConsole.hpp"

Creature::Creature(std::string_view typeName)
{
    type_ = Hash(typeName);
}

Creature::Creature(int type)
{
    type_ = type;

    auto typeName{_<CreatureIndex>().GetCreatureLabel(type)};
}

void Creature::Hit(float damage, PointF hitPosition)
{
    health_ -= damage;

    ticksLastHitOnSelf_ = Now();

    lastHitPosition_ = hitPosition;

    targetingPlayer_ = true;

    auto now{Now()};

    if (now - ticksLastHitOnOther_ > InvertSpeed(attackSpeed_))
    {
        ticksLastHitOnOther_ = now;
    }

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