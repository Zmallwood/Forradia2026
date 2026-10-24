//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GUI8COMPONENT.HPP"

namespace FORRADIA8GAME {
    class GUI8PANEL : public GUI8COMPONENT {
      public:
        GUI8PANEL(float x, float y, float width, float height);

        SIZE8F mSize{0.0F, 0.0F};

      protected:
        virtual bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

        virtual void RENDER8DERIVED() override;

        virtual std::string GET8BACKGROUND8IMAGE();

        RECT8F GET8BOUNDS();

      private:
        inline static const std::string mkDefaultBackgroundImage{
            "GUIPanelBackground"};
    };
}