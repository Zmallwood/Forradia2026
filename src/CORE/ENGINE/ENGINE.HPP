//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class ENGINE {
      public:
        void START();

        void STOP();

      private:
        void RANDOMIZE();

        void POLL_EVENTS();

        bool running_{true};
        int ticksLeftMouseButtonDown_{0};
        int ticksRightMouseButtonDown_{0};
    };
}