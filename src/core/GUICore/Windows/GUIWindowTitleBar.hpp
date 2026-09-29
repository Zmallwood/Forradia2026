/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "Core/GUICore/GUIPanel.hpp"

namespace Forradia
{
    class GUIWindow;

    class GUIWindowTitleBar : public GUIPanel
    {
      public:
        GUIWindowTitleBar(std::string_view title, float width,
                          GUIWindow &guiWindow);

      protected:
        void UpdateDerived() override;

        void RenderDerived() override;

        bool OnMouseDown(Uint8 mouseButton) override;

        bool OnMouseUp(Uint8 mouseButton, int clickSpeed) override;

        virtual std::string GetBackgroundImage() override;

        PointF GetPosition() override;

        void SetPosition(PointF value) override;

      private:
        inline static const std::string k_defaultBackgroundImage_{
            "GUIWindowTitleBarBackground"};
        static constexpr PointF k_margin_{0.01F, 0.01F};

        GUIWindow &guiWindow_;
        std::string title_;
        PointF positionStartMove_;
        PointF mousePositionStartMove_;
        bool isMoving_{false};
    };
}