//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA
{
    class CreatureRespawner
    {
      public:
        void Update();

        void RespawnCreature(int creatureType, int respawnTimeMillis);

      private:
        std::unordered_multimap<int, int> creatureRespawns_;
    };
}