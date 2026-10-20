// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "FONT_SIZES.HPP"

class TextRenderer
{
  public:
    void Initialize();

    void DrawString(std::string_view text, float x, float y,
                    FontSizes fontSize = FontSizes::_12, bool centered = false,
                    COLOR color = COLORS::kWheat);

  private:
    void AddFont(FontSizes fontSize);

    const std::string kDefaultFontPath_ = "./resources/Fonts/PixeloidSans.ttf";
    std::unordered_map<FontSizes, std::shared_ptr<TTF_Font>> fonts_;
};