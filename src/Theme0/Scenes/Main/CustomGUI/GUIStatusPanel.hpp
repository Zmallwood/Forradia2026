/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Core/GUICore/GUIPanel.hpp"

namespace Forradia
{
    class GUIStatusPanel : public GUIPanel
    {
      public:
        GUIStatusPanel();

      protected:
        void RenderDerived() override;
    };
}