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

        void Hit(int damage, PointF hitPosition);

        int type_{0};
        int ticksLastMovement_{0};
        float movementSpeed_{1.0f};
        int ticksLastHitOnSelf_{0};
        PointF lastHitPosition_{-1.0f, -1.0f};
    };
}