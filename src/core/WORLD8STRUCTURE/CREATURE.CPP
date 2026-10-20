// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CREATURE.HPP"
#include "CORE/CONFIGURATION/CREATURE8INDEX.HPP"
#include "CORE/GUI8CORE/GUI_TEXT_CONSOLE.HPP"

Creature::Creature(std::string_view typeName)
{
    type_ = HASH(typeName);
}

Creature::Creature(int type)
{
    type_ = type;

    auto typeName = _<CREATURE8INDEX>().GET8CREATURE8LABEL(type);
}

void Creature::Hit(float damage, POINT8F hitPosition)
{
    health_ -= damage;

    ticksLastHitOnSelf_ = NOW();

    lastHitPosition_ = hitPosition;

    targetingPlayer_ = true;

    auto now = NOW();

    if (now - ticksLastHitOnOther_ > INVERT8SPEED(attackSpeed_))
    {
        ticksLastHitOnOther_ = now;
    }

    auto creatureLabel = _<CREATURE8INDEX>().GET8CREATURE8LABEL(type_);

    std::stringstream ssDamage;

    ssDamage << std::fixed << std::setprecision(1) << damage;

    _<GUITextConsole>().PrintLine("You hit a " + creatureLabel + " for " +
                                  ssDamage.str() + " damage.");
}

bool Creature::IsDead()
{
    return health_ <= 0.0f;
}