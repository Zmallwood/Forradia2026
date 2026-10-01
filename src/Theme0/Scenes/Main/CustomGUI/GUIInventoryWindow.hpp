/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "Core/GUICore/Windows/GUIWindow.hpp"

namespace Forradia
{
    class GUIInventoryWindow : public GUIWindow
    {
      public:
        GUIInventoryWindow();

      protected:
        bool OnMouseDown(Uint8 mouseButton) override;

        bool OnMouseUp(Uint8 mouseButton, int clickSpeed) override;

        void RenderDerived() override;

      private:
        static constexpr float k_slotWidth_{0.037f};
        static constexpr float k_slotMarginX_{0.005f};
    };
}