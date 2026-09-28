/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUITextConsole : public GUIPanel
    {
      public:
        GUITextConsole();

        void PrintLine(std::string_view line);

      protected:
        void RenderDerived() override;

      private:
        static constexpr float k_lineHeight_{0.02f};

        std::vector<std::string> lines_;
    };
}