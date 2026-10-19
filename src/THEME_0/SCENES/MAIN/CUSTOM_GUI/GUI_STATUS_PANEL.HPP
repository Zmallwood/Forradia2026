// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/GUI_CORE/GUI_PANEL.HPP"

class GUIStatusPanel : public GUIPanel
{
  public:
    GUIStatusPanel();

  protected:
    void RenderDerived() override;
};