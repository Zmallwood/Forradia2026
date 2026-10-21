//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "CORE/GUI8CORE/WINDOWS/GUI8WINDOW.HPP"

namespace FORRADIA8GAME {
    class GUI8EQUIPMENT8WINDOW : public GUI8WINDOW {
      public:
        GUI8EQUIPMENT8WINDOW();

      protected:
        bool ON8MOUSE8DOWN(Uint8 mouseButton) override;

        bool ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) override;

        void RENDER8DERIVED() override;

      private:
        RECT8F GET8HEAD8SLOT8BOUNDS();

        RECT8F GET8CHEST8SLOT8BOUNDS();

        RECT8F GET8LEGS8SLOT8BOUNDS();

        RECT8F GET8FEET8SLOT8BOUNDS();

        RECT8F GET8RIGHT8HAND8SLOT8BOUNDS();

        RECT8F GET8LEFT8HAND8SLOT8BOUNDS();

        static constexpr float kSlotWidth_{0.037f};
        static constexpr float kMarginY_{0.02f};
        static constexpr std::string_view kHeadSlotImage_{
            "GUIEquipmentWindowHeadSlotBackground"};
        static constexpr std::string_view kChestSlotImage_{
            "GUIEquipmentWindowChestSlotBackground"};
        static constexpr std::string_view kLegsSlotImage_{
            "GUIEquipmentWindowLegsSlotBackground"};
        static constexpr std::string_view kFeetSlotImage_{
            "GUIEquipmentWindowFeetSlotBackground"};
        static constexpr std::string_view kRightHandSlotImage_{
            "GUIEquipmentWindowRightHandSlotBackground"};
        static constexpr std::string_view kLeftHandSlotImage_{
            "GUIEquipmentWindowLeftHandSlotBackground"};
    };
}