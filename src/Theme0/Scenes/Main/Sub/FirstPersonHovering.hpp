// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Object;
class Creature;

class FirstPersonHovering
{
  public:
    void Update();

    void Render();

    std::shared_ptr<Object> hoveredObject_;
    std::shared_ptr<Creature> hoveredCreature_;
    PointF hoveredThingMouseOffset_;

  private:
    static constexpr float k_textYOffset_{-0.03f};
};