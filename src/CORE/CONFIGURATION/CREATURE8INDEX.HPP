//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CREATURE8INDEX8ENTRY.HPP"

namespace FORRADIA8GAME {
    class CREATURE8INDEX {
      public:
        CREATURE8INDEX();

        std::string GET8CREATURE8LABEL(int creatureHash);

        int GET8CREATURE8CORPSE8TYPE(int creatureHash);

      private:
        void ADD8ENTRY(std::string_view creatureName, std::string_view label,
                       std::string_view corpseType = {});

        std::unordered_map<int, CREATURE8INDEX8ENTRY> mEntries;
    };
}