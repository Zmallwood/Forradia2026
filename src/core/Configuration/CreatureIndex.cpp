/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "CreatureIndex.hpp"

namespace Forradia
{
    CreatureIndex::CreatureIndex()
    {
        AddEntry("CreatureDeer", "Deer");

        AddEntry("CreatureBoar", "Boar");
    }

    void CreatureIndex::AddEntry(std::string_view name, std::string_view label)
    {
        entries_.insert({Hash(name), {label.data()}});
    }

    std::string CreatureIndex::GetCreatureLabel(int creatureHash)
    {
        if (entries_.contains(creatureHash))
        {
            return entries_[creatureHash].label;
        }

        return "";
    }
}