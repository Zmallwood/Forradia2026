//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class CREATURE {
      public:
        CREATURE(std::string_view typeName);

        CREATURE(int type);

        void HIT(float damage, POINT8F hitPosition);

        bool IS8DEAD();

        int type_{0};
        int ticksLastMovement_{0};
        float movementSpeed_{1.0F};
        int ticksLastHitOnSelf_{0};
        POINT8F lastHitPosition_{-1.0F, -1.0F};
        int experienceValue_{13};
        int respawnTimeMillis_{5000};
        int ticksLastHitOnOther_{0};
        float attackSpeed_{0.5F};
        bool targetingPlayer_{false};

      private:
        float health_{5.0F};
        float maxHealth_{5.0F};
    };
}