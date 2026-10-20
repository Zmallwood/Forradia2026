// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class GAME8PROPERTIES
{
  public:
    static constexpr SIZE kWorldAreaSize_ = {100, 100};
    static constexpr float kTileWidth_ = 0.07f;
    static constexpr int kTileGridSize_ = 15;
    static constexpr int kTileUnitsWidth_ = 20;
    static constexpr float kViewWidth_ = 0.5f;
    static constexpr float kLargeObjectScale_ = 0.35f;
    static constexpr float kSmallObjectScale_ = 0.08f;
    static constexpr POINT8F kFirstPersonViewMargin_ = {0.03f, 0.01f};
    static constexpr float kImpactPointWidth_ = 0.005f;
};