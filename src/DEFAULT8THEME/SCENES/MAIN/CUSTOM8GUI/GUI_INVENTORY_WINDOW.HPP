// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/WINDOWS/GUI8WINDOW.HPP"

class GUIInventoryWindow : public GUI8WINDOW
{
  public:
    GUIInventoryWindow();

  protected:
    bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

    bool ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) override;

    void RENDER8DERIVED() override;

  private:
    static constexpr float k_slotWidth_ = 0.037f;
    static constexpr float k_slotMarginX_ = 0.005f;
};