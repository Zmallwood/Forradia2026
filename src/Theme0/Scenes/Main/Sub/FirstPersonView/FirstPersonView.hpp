/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class FirstPersonView
    {
      public:
        void Render();

      private:
        static constexpr int k_hitOtherEffectDuration_{250};
        static constexpr int k_hitSelfEffectDuration_{100};
        static constexpr float k_wieldedObjectScale_{0.15f};
    };
}