//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CREATURE8INDEX.HPP"

namespace FORRADIA
{
    CREATURE8INDEX::CREATURE8INDEX()
    {
        ADD8ENTRY("CreatureDeer", "Deer", "ObjectCreatureDeerCorpse");

        ADD8ENTRY("CreatureBoar", "Boar", "ObjectCreatureBoarCorpse");
    }

    void
    CREATURE8INDEX::ADD8ENTRY(std::string_view name, std::string_view label,
                              std::string_view corpseType)
    {
        entries_.insert({HASH(name), {label.data(), HASH(corpseType)}});
    }

    std::string
    CREATURE8INDEX::GET8CREATURE8LABEL(int creatureHash)
    {
        if (entries_.contains(creatureHash))
        {
            return entries_[creatureHash].label;
        }

        return "";
    }

    int
    CREATURE8INDEX::GET8CREATURE8CORPSE8TYPE(int creatureHash)
    {
        if (entries_.contains(creatureHash))
        {
            return entries_[creatureHash].corpseType;
        }

        return 0;
    }
}