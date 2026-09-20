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
        static constexpr PointF k_margin_{0.03f, 0.01f};
    };
}