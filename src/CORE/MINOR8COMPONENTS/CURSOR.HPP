//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CURSOR8STYLES.HPP"

namespace FORRADIA8GAME {
    class CURSOR {
      public:
        CURSOR();

        void RESET();

        void RENDER();

        CURSOR8STYLES mCursorStyle{CURSOR8STYLES::Default};

      private:
        static constexpr float mkCursorSize{0.05F};
    };
}