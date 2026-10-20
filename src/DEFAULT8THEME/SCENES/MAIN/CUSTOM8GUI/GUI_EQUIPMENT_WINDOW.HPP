//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/GUI8CORE/WINDOWS/GUI8WINDOW.HPP"

namespace FORRADIA8GAME
{
    class GUIEquipmentWindow : public GUI8WINDOW
    {
      public:
        GUIEquipmentWindow();

      protected:
        bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

        bool ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) override;

        void RENDER8DERIVED() override;

      private:
        RECT8F GetHeadSlotBounds();

        RECT8F GetChestSlotBounds();

        RECT8F GetLegsSlotBounds();

        RECT8F GetFeetSlotBounds();

        RECT8F GetRightHandSlotBounds();

        RECT8F GetLeftHandSlotBounds();

        static constexpr float kSlotWidth_ = 0.037f;
        static constexpr float kMarginY_ = 0.02f;
        static constexpr std::string_view kHeadSlotImage_ =
            "GUIEquipmentWindowHeadSlotBackground";
        static constexpr std::string_view kChestSlotImage_ =
            "GUIEquipmentWindowChestSlotBackground";
        static constexpr std::string_view kLegsSlotImage_ =
            "GUIEquipmentWindowLegsSlotBackground";
        static constexpr std::string_view kFeetSlotImage_ =
            "GUIEquipmentWindowFeetSlotBackground";
        static constexpr std::string_view kRightHandSlotImage_ =
            "GUIEquipmentWindowRightHandSlotBackground";
        static constexpr std::string_view kLeftHandSlotImage_ =
            "GUIEquipmentWindowLeftHandSlotBackground";
    };
}