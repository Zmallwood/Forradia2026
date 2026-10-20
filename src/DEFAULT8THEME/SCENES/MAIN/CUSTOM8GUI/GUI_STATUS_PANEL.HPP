//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CORE/GUI8CORE/GUI8PANEL.HPP"

namespace FORRADIA8GAME
{
    class GUIStatusPanel : public GUI8PANEL
    {
      public:
        GUIStatusPanel();

      protected:
        void RENDER8DERIVED() override;
    };
}