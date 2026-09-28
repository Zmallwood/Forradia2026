/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class GUIPanel : public GUIComponent
    {
      public:
        GUIPanel(float x, float y, float width, float height);

      protected:
        virtual void RenderDerived() override;

        virtual std::string GetBackgroundImage();

        RectF GetBounds();

        SizeF size_{0.0f, 0.0f};

      private:
        inline static const std::string k_defaultBackgroundImage_{
            "GUIPanelBackground"};
    };
}