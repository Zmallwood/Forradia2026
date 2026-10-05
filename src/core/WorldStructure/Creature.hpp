// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Creature
{
  public:
    Creature(std::string_view typeName);

    Creature(int type);

    void Hit(float damage, PointF hitPosition);

    bool IsDead();

    int type_{0};
    int ticksLastMovement_{0};
    float movementSpeed_{1.0f};
    int ticksLastHitOnSelf_{0};
    PointF lastHitPosition_{-1.0f, -1.0f};
    int experienceValue_{13};
    int respawnTimeMillis_{5000};
    int ticksLastHitOnOther_{0};
    float attackSpeed_{0.5f};
    bool targetingPlayer_{false};

  private:
    float health_{5.0f};
    float maxHealth_{5.0f};
};