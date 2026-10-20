// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "CORE/WORLD_STRUCTURE/WORLD_DIRECTIONS.HPP"

class PlayerInventory;
class PlayerEquipment;

class Player
{
  public:
    Player();

    void MoveNorth();

    void MoveEast();

    void MoveSouth();

    void MoveWest();

    void TurnNorth();

    void TurnEast();

    void TurnSouth();

    void TurnWest();

    void AddExperience(int amount);

    void Hit(float damage);

    void SpawnOnSuitableLocation();

    POINT8F position_ = {0.0f, 0.0f};
    int ticksLastMovement_ = 0;
    float movementSpeed_ = 11.0f;
    float stepSize_ = 0.3f;
    POINT destination_ = {-1, -1};
    POINT facedTileCoordinate_ = {-1, -1};
    WorldDirections facingDirection_ = WorldDirections::South;
    int ticksLastHitOnOther_ = 0;
    float attackSpeed_ = 2.0f;
    std::string name_ = "Unnamed player";
    int experience_ = 0;
    std::shared_ptr<PlayerInventory> playerInventory_;
    float health_ = 10.0f;
    float maxHealth_ = 10.0f;
    int ticksLastHitOnSelf_ = 0;
    std::shared_ptr<PlayerEquipment> playerEquipment_;
    int ticksLastImpact_ = 0;
    float impactSpeed_ = 1.0f;
};