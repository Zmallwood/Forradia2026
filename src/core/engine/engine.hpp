/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Engine
    {
      public:
        void Start();

      private:
        void PollEvents();

        bool running_{true};
        int ticksLeftMouseButtonDown_{0};
        int ticksRightMouseButtonDown_{0};
    };
}