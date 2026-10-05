// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CompletedObjectImpact.hpp"

class FirstPersonView
{
  public:
    void Update();

    void Render();

    std::vector<CompletedObjectImpact> completedObjectImpacts_;

  private:
    static constexpr int k_hitOtherEffectDuration_{100};
    static constexpr int k_hitSelfEffectDuration_{100};
    static constexpr int k_impactPointEffectDuration_{100};
    static constexpr float k_wieldedObjectScale_{0.15f};
};