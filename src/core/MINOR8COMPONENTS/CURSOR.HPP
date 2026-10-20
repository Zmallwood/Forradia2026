//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CURSOR8STYLES.HPP"

namespace FORRADIA
{
    class CURSOR
    {
      public:
        CURSOR();

        void RESET();

        void RENDER();

        CURSOR8STYLES cursorStyle_ = CURSOR8STYLES::Default;

      private:
        static constexpr float kCursorSize_ = 0.05f;
    };
}