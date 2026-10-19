// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/GUI_CORE/WINDOWS/GUI_WINDOW.HPP"

class GUIEquipmentWindow : public GUIWindow
{
  public:
    GUIEquipmentWindow();

  protected:
    bool OnMouseDown(Uint8 mouseButton) override;

    bool OnMouseUp(Uint8 mouseButton, int clickSpeed) override;

    void RenderDerived() override;

  private:
    RECT_F GetHeadSlotBounds();

    RECT_F GetChestSlotBounds();

    RECT_F GetLegsSlotBounds();

    RECT_F GetFeetSlotBounds();

    RECT_F GetRightHandSlotBounds();

    RECT_F GetLeftHandSlotBounds();

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