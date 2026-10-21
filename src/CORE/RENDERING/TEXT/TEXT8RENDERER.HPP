//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "FONT8SIZES.HPP"

namespace FORRADIA8GAME {
    class TEXT8RENDERER {
      public:
        void INITIALIZE();

        void DRAW8STRING(std::string_view text, float x, float y,
                         FONT8SIZES fontSize = FONT8SIZES::_15,
                         bool centered = false, COLOR color = COLORS::kWheat);

        SIZE8F MEASURE8STRING(std::string_view text,
                              FONT8SIZES fontSize = FONT8SIZES::_15);

      private:
        void ADD8FONT(FONT8SIZES fontSize);

        const std::string kDefaultFontPath_{
            "./resources/Fonts/PixeloidSans.ttf"};
        std::unordered_map<FONT8SIZES, std::shared_ptr<TTF_Font>> fonts_;
    };
}