//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class FPS8COUNTER {
      public:
        void UPDATE();

        void RENDER();

      private:
        int mFPS{0};
        int mFramesCounter{0};
        int mTicksLastUpdate{0};
    };
}