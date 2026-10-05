// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CreatureIndex.hpp"

CreatureIndex::CreatureIndex()
{
    AddEntry("CreatureDeer", "Deer", "ObjectCreatureDeerCorpse");

    AddEntry("CreatureBoar", "Boar", "ObjectCreatureBoarCorpse");
}

void CreatureIndex::AddEntry(std::string_view name, std::string_view label,
                             std::string_view corpseType)
{
    entries_.insert({Hash(name), {label.data(), Hash(corpseType)}});
}

std::string CreatureIndex::GetCreatureLabel(int creatureHash)
{
    if (entries_.contains(creatureHash))
    {
        return entries_[creatureHash].label;
    }

    return "";
}

int CreatureIndex::GetCreatureCorpseType(int creatureHash)
{
    if (entries_.contains(creatureHash))
    {
        return entries_[creatureHash].corpseType;
    }

    return 0;
}