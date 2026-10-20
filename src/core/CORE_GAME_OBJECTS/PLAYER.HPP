//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/WORLD8STRUCTURE/WORLD8DIRECTIONS.HPP"

namespace FORRADIA
{
    class PLAYER8INVENTORY;
    class PLAYER8EQUIPMENT;

    class PLAYER
    {
      public:
        PLAYER();

        void MOVE8NORTH();

        void MOVE8EAST();

        void MOVE8SOUTH();

        void MOVE8WEST();

        void TURN8NORTH();

        void TURN8EAST();

        void TURN8SOUTH();

        void TURN8WEST();

        void ADD8EXPERIENCE(int amount);

        void HIT(float damage);

        void SPAWN8ONSUITABLE8LOCATION();

        POINT8F position_ = {0.0f, 0.0f};
        int ticksLastMovement_ = 0;
        float movementSpeed_ = 11.0f;
        float stepSize_ = 0.3f;
        POINT destination_ = {-1, -1};
        POINT facedTileCoordinate_ = {-1, -1};
        WORLD8DIRECTIONS facingDirection_ = WORLD8DIRECTIONS::South;
        int ticksLastHitOnOther_ = 0;
        float attackSpeed_ = 2.0f;
        std::string name_ = "Unnamed player";
        int experience_ = 0;
        std::shared_ptr<PLAYER8INVENTORY> playerInventory_;
        float health_ = 10.0f;
        float maxHealth_ = 10.0f;
        int ticksLastHitOnSelf_ = 0;
        std::shared_ptr<PLAYER8EQUIPMENT> playerEquipment_;
        int ticksLastImpact_ = 0;
        float impactSpeed_ = 1.0f;
    };
}