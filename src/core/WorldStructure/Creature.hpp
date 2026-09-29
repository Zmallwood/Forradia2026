/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Creature
    {
      public:
        Creature(std::string_view typeName);

        void Hit(float damage, PointF hitPosition);

        bool IsDead();

        int type_{0};
        int corpesType_{0};
        int ticksLastMovement_{0};
        float movementSpeed_{1.0f};
        int ticksLastHitOnSelf_{0};
        PointF lastHitPosition_{-1.0f, -1.0f};
        int experienceValue_{13};

      private:
        float health_{5.0f};
        float maxHealth_{5.0f};
    };
}