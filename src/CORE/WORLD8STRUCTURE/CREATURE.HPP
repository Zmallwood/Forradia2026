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

        int mType{0};
        int mTicksLastMovement{0};
        float mMovementSpeed{1.0F};
        int mTicksLastHitOnSelf{0};
        POINT8F mLastHitPosition{-1.0F, -1.0F};
        int mExperienceValue{13};
        int mRespawnTimeMillis{5000};
        int mTicksLastHitOnOther{0};
        float mAttackSpeed{0.5F};
        bool mTargetingPlayer{false};

      private:
        float mHealth{5.0F};
        float mMaxHealth{5.0F};
    };
}