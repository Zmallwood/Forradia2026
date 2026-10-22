//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CORE/GUI8CORE/GUI8PANEL.HPP"

namespace FORRADIA8GAME {
    class GUI8ESSENCE8PANEL : public GUI8PANEL {
      public:
        GUI8ESSENCE8PANEL();

      protected:
        void RENDER8DERIVED() override;
    };
}