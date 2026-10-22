//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "COMPLETED8OBJECT8IMPACT.HPP"

namespace FORRADIA8GAME {
    class FIRST8PERSON8VIEW {
      public:
        void UPDATE();

        void RENDER();

        std::vector<COMPLETED8OBJECT8IMPACT> completedObjectImpacts_;

      private:
        static constexpr int kHitOtherEffectDuration_{100};
        static constexpr int kHitSelfEffectDuration_{100};
        static constexpr int kImpactPointEffectDuration_{100};
        static constexpr float kWieldedObjectScale_{0.15F};
        static constexpr float kHandsOpacity_{0.5F};
        static constexpr float kBorderWidth_{0.01F};
    };
}