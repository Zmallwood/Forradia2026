//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GUI8PANEL.HPP"

namespace FORRADIA8GAME {
    class GUI8BUTTON : public GUI8PANEL {
      public:
        GUI8BUTTON(std::string_view text, float x, float y, float width,
                   float height, std::function<void()> action,
                   std::string_view backgroundImage = "GUIButtonBackground",
                   std::string_view hoveredBackgroundImage =
                       "GUIButtonHoveredBackground");

      protected:
        void UPDATE8DERIVED() override;

        void RENDER8DERIVED() override;

        bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

        std::string GET8BACKGROUND8IMAGE() override;

      private:
        const std::string kBackgroundImage_{"GUIButtonBackground"};
        const std::string kHoveredBackgroundImage_{
            "GUIButtonHoveredBackground"};

        std::string text_;
        std::function<void()> action_;
        bool hovered_{false};
    };
}