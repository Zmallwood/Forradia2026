//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GUI8ACTION8MENU8ENTRY.HPP"

namespace FORRADIA8GAME
{
    class GUI8ACTION8MENU
    {
      public:
        void OnMouseDown(Uint8 mouseButton);

        void Render();

      private:
        static constexpr float kWidth = 0.1f;
        static constexpr float kLineHeight = 0.02f;
        static constexpr float kMarginX = 0.002f;
        POINT8F rightClickMousePosition_;
        std::vector<GUI8ACTION8MENU8ENTRY> entries_;
        bool visible_ = false;
    };
}