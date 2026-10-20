//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/GUI8CORE/GUI8PANEL.HPP"

namespace FORRADIA
{
    class GUI8WINDOW8TITLE8BAR;

    class GUI8WINDOW : public GUI8PANEL
    {
      public:
        GUI8WINDOW(std::string_view title, float x, float y, float width,
                   float height);

        void TOGGLE8VISIBILITY();

        std::shared_ptr<GUI8WINDOW8TITLE8BAR> titleBar_;
    };
}