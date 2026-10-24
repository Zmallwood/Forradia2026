//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/WORLD8STRUCTURE/COMPASS8DIRECTIONS.HPP"

namespace FORRADIA8GAME {
    class PLAYER8INVENTORY;
    class PLAYER8EQUIPMENT;

    class PLAYER {
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

        POINT8F mPosition{0.0F, 0.0F};
        int mTicksLastMovement{0};
        float mMovementSpeed{11.0F};
        float mStepSize{0.3F};
        POINT mDestination{-1, -1};
        POINT mFacedTileCoordinate{-1, -1};
        COMPASS8DIRECTIONS mFacingDirection{COMPASS8DIRECTIONS::South};
        int mTicksLastHitOnOther{0};
        float mAttackSpeed{2.0F};
        std::string mName{"Unnamed player"};
        int mExperience{0};
        std::shared_ptr<PLAYER8INVENTORY> mPlayerInventory;
        float mHealth{10.0F};
        float mMaxHealth{10.0F};
        int mTicksLastHitOnSelf{0};
        std::shared_ptr<PLAYER8EQUIPMENT> mPlayerEquipment;
        int mTicksLastImpact{0};
        float mImpactSpeed{1.0F};
    };
}