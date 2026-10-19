// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class GameProperties
{
  public:
    static constexpr SIZE k_worldAreaSize_ = {100, 100};
    // static constexpr float k_tileWidth_ = 0.05f;
    static constexpr float k_tileWidth_ = 0.07f;
    static constexpr int k_tileGridSize_ = 15;
    static constexpr int k_tileUnitsWidth_ = 20;
    static constexpr float k_viewWidth_ = 0.5f;
    static constexpr float k_largeObjectScale_ = 0.35f;
    static constexpr float k_smallObjectScale_ = 0.08f;
    static constexpr POINT_F k_firstPersonViewMargin_ = {0.03f, 0.01f};
    static constexpr float k_impactPointWidth_ = 0.005f;
};