//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GUI8PANEL.HPP"

namespace FORRADIA8GAME {
    class GUI8TEXT8CONSOLE : public GUI8PANEL {
      public:
        GUI8TEXT8CONSOLE();

        void PRINT8LINE(std::string_view line);

      protected:
        void RENDER8DERIVED() override;

      private:
        static constexpr float mkLineHeight{0.02F};

        std::vector<std::string> mLines;
    };
}