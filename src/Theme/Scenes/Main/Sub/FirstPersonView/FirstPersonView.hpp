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
        static constexpr int k_hitEffectDuration_{500};
    };
}