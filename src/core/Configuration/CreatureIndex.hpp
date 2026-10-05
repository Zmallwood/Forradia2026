// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CreatureIndexEntry.hpp"

class CreatureIndex
{
  public:
    CreatureIndex();

    std::string GetCreatureLabel(int creatureHash);

    int GetCreatureCorpseType(int creatureHash);

  private:
    void AddEntry(std::string_view creatureName, std::string_view label,
                  std::string_view corpseType = {});

    std::unordered_map<int, CreatureIndexEntry> entries_;
};