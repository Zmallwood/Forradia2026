//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CORE/GUI8CORE/GUI8PANEL.HPP"

namespace FORRADIA8GAME {
    class GUI8STATUS8PANEL : public GUI8PANEL {
      public:
        GUI8STATUS8PANEL();

      protected:
        void RENDER8DERIVED() override;
    };
}