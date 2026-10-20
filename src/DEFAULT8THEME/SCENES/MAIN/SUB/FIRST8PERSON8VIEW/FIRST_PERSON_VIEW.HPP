//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "COMPLETED_OBJECT_IMPACT.HPP"

namespace FORRADIA8GAME
{
    class FirstPersonView
    {
      public:
        void Update();

        void Render();

        std::vector<CompletedObjectImpact> completedObjectImpacts_;

      private:
        static constexpr int kHitOtherEffectDuration_ = 100;
        static constexpr int kHitSelfEffectDuration_ = 100;
        static constexpr int kImpactPointEffectDuration_ = 100;
        static constexpr float kWieldedObjectScale_ = 0.15f;
        static constexpr float kHandsOpacity_ = 0.5f;
    };
}