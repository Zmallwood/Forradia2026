// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "Player.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "PlayerEquipment.hpp"
#include "PlayerInventory.hpp"

Player::Player()
    : playerInventory_(std::make_shared<PlayerInventory>()),
      playerEquipment_(std::make_shared<PlayerEquipment>())
{
    playerInventory_->AddObject("ObjectRedApple");

    playerInventory_->AddObject("ObjectCopperSword");

    playerInventory_->AddObject("ObjectWoodAxe");

    playerInventory_->AddObject("ObjectSaw");

    playerInventory_->AddObject("ObjectHammer");
}

void Player::SpawnOnSuitableLocation()
{
    auto worldArea = _<World>().currentWorldArea_;

    auto worldAreaSize = worldArea->GetSize();

    position_ = {4.0f + (worldAreaSize.width - 5.0f) / 2,
                 4.0f + (worldAreaSize.height - 5.0f) / 2};

    auto tile = worldArea->GetTile(static_cast<int>(position_.x),
                                   static_cast<int>(position_.y));

    while (tile->ground_ == Hash("GroundWater"))
    {
        position_ = {4.0f + (rand() % (worldAreaSize.width - 5)),
                     4.0f + (rand() % (worldAreaSize.height - 5))};

        tile = worldArea->GetTile(static_cast<int>(position_.x),
                                  static_cast<int>(position_.y));
    }

    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) + 1};
}

void Player::MoveNorth()
{
    auto newX = position_.x;
    auto newY = position_.y - stepSize_;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) - 1};

    facingDirection_ = WorldDirections::North;
}

void Player::MoveEast()
{
    auto newX = position_.x + stepSize_;
    auto newY = position_.y;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x) + 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::East;
}

void Player::MoveSouth()
{
    auto newX = position_.x;
    auto newY = position_.y + stepSize_;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) + 1};

    facingDirection_ = WorldDirections::South;
}

void Player::MoveWest()
{
    auto newX = position_.x - stepSize_;
    auto newY = position_.y;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x) - 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::West;
}

void Player::TurnNorth()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) - 1};

    facingDirection_ = WorldDirections::North;
}

void Player::TurnEast()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x) + 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::East;
}

void Player::TurnSouth()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) + 1};

    facingDirection_ = WorldDirections::South;
}

void Player::TurnWest()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x) - 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::West;
}

void Player::AddExperience(int amount)
{
    experience_ += amount;

    _<GUITextConsole>().PrintLine("You gained " + std::to_string(amount) +
                                  " experience points.");
}

void Player::Hit(float damage)
{
    health_ -= damage;

    ticksLastHitOnSelf_ = Now();

    std::stringstream ssDamage;
    
    ssDamage << std::fixed << std::setprecision(1) << damage;

    _<GUITextConsole>().PrintLine("You took " + ssDamage.str() + " damage.");
}