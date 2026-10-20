//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/GUI8CORE/GUI8PANEL.HPP"

namespace FORRADIA8GAME {
    class GUI8WINDOW;

    class GUI8WINDOW8TITLE8BAR : public GUI8PANEL {
      public:
        GUI8WINDOW8TITLE8BAR(std::string_view title, float width,
                             GUI8WINDOW &guiWindow);

      protected:
        void UPDATE8DERIVED() override;

        void RENDER8DERIVED() override;

        bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

        bool ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) override;

        virtual std::string GET8BACKGROUND8IMAGE() override;

        POINT8F GET8POSITION() override;

        void SET8POSITION(POINT8F value) override;

      private:
        inline static const std::string kDefaultBackgroundImage_ =
            "GUIWindowTitleBarBackground";
        static constexpr POINT8F kMargin_ = {0.01F, 0.01F};

        GUI8WINDOW &guiWindow_;
        std::string title_;
        POINT8F positionStartMove_;
        POINT8F mousePositionStartMove_;
        bool isMoving_{false};
    };
}