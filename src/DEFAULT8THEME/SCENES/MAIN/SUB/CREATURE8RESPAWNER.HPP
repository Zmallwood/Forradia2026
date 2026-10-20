//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class CREATURE8RESPAWNER {
      public:
        void UPDATE();

        void RESPAWN8CREATURE(int creatureType, int respawnTimeMillis);

      private:
        std::unordered_multimap<int, int> creatureRespawns_;
    };
}