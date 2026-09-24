/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Player
    {
      public:
        Player();

        void MoveNorth();

        void MoveEast();

        void MoveSouth();

        void MoveWest();

        void TurnNorth();

        void TurnEast();

        void TurnSouth();

        void TurnWest();

        Point position_{0, 0};
        int ticksLastMovement_{0};
        float movementSpeed_{4.0f};
        Point destination_{-1, -1};
        Point facedTile_{-1, -1};
        WorldDirections facingDirection_{WorldDirections::South};
        int ticksLastHitOnOther_{0};
        float attackSpeed_{2.0f};

      private:
        void SpawnOnSuitableLocation();
    };
}