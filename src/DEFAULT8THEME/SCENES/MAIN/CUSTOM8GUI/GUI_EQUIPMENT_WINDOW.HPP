// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI8CORE/WINDOWS/GUI8WINDOW.HPP"

class GUIEquipmentWindow : public GUI8WINDOW
{
  public:
    GUIEquipmentWindow();

  protected:
    bool OnMouseDown(Uint8 mouseButton) override;

    bool OnMouseUp(Uint8 mouseButton, int clickSpeed) override;

    void RenderDerived() override;

  private:
    RECT8F GetHeadSlotBounds();

    RECT8F GetChestSlotBounds();

    RECT8F GetLegsSlotBounds();

    RECT8F GetFeetSlotBounds();

    RECT8F GetRightHandSlotBounds();

    RECT8F GetLeftHandSlotBounds();

    static constexpr float k_slotWidth_ = 0.037f;
    static constexpr float k_marginY_ = 0.02f;
    static constexpr std::string_view k_headSlotImage_ =
        "GUIEquipmentWindowHeadSlotBackground";
    static constexpr std::string_view k_chestSlotImage_ =
        "GUIEquipmentWindowChestSlotBackground";
    static constexpr std::string_view k_legsSlotImage_ =
        "GUIEquipmentWindowLegsSlotBackground";
    static constexpr std::string_view k_feetSlotImage_ =
        "GUIEquipmentWindowFeetSlotBackground";
    static constexpr std::string_view k_rightHandSlotImage_ =
        "GUIEquipmentWindowRightHandSlotBackground";
    static constexpr std::string_view k_leftHandSlotImage_ =
        "GUIEquipmentWindowLeftHandSlotBackground";
};