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
    auto worldArea{_<World>().currentWorldArea_};

    auto worldAreaSize{worldArea->GetSize()};

    position_ = {worldAreaSize.width / 2, worldAreaSize.height / 2};

    auto tile{worldArea->GetTile(position_)};

    while (tile->ground_ == Hash("GroundWater"))
    {
        position_ = {rand() % worldAreaSize.width,
                     rand() % worldAreaSize.height};
        tile = worldArea->GetTile(position_);
    }

    facedTileCoordinate_ = {position_.x, position_.y + 1};
}

void Player::MoveNorth()
{
    auto newX{position_.x};
    auto newY{position_.y - 1};

    auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {position_.x, position_.y - 1};

    facingDirection_ = WorldDirections::North;
}

void Player::MoveEast()
{
    auto newX{position_.x + 1};
    auto newY{position_.y};

    auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {position_.x + 1, position_.y};

    facingDirection_ = WorldDirections::East;
}

void Player::MoveSouth()
{
    auto newX{position_.x};
    auto newY{position_.y + 1};

    auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {position_.x, position_.y + 1};

    facingDirection_ = WorldDirections::South;
}

void Player::MoveWest()
{
    auto newX{position_.x - 1};
    auto newY{position_.y};

    auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

    if (newTile &&
        (newTile->ground_ == Hash("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {position_.x - 1, position_.y};

    facingDirection_ = WorldDirections::West;
}

void Player::TurnNorth()
{
    facedTileCoordinate_ = {position_.x, position_.y - 1};

    facingDirection_ = WorldDirections::North;
}

void Player::TurnEast()
{
    facedTileCoordinate_ = {position_.x + 1, position_.y};

    facingDirection_ = WorldDirections::East;
}

void Player::TurnSouth()
{
    facedTileCoordinate_ = {position_.x, position_.y + 1};

    facingDirection_ = WorldDirections::South;
}

void Player::TurnWest()
{
    facedTileCoordinate_ = {position_.x - 1, position_.y};

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