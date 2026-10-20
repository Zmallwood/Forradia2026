// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "PLAYER.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/GUI8CORE/GUI8TEXT8CONSOLE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"
#include "PLAYER8EQUIPMENT.HPP"
#include "PLAYER8INVENTORY.HPP"

PLAYER::PLAYER()
    : playerInventory_(std::make_shared<PLAYER8INVENTORY>()),
      playerEquipment_(std::make_shared<PLAYER8EQUIPMENT>())
{
    playerInventory_->ADD8OBJECT("ObjectRedApple");

    playerInventory_->ADD8OBJECT("ObjectCopperSword");

    playerInventory_->ADD8OBJECT("ObjectWoodAxe");

    playerInventory_->ADD8OBJECT("ObjectSaw");

    playerInventory_->ADD8OBJECT("ObjectHammer");
}

void PLAYER::SPAWN8ONSUITABLE8LOCATION()
{
    auto worldArea = _<World>().currentWorldArea_;

    auto worldAreaSize = worldArea->GetSize();

    position_ = {4.0f + (worldAreaSize.width - 5.0f) / 2,
                 4.0f + (worldAreaSize.height - 5.0f) / 2};

    auto tile = worldArea->GetTile(static_cast<int>(position_.x),
                                   static_cast<int>(position_.y));

    while (tile->ground_ == HASH("GroundWater"))
    {
        position_ = {4.0f + (rand() % (worldAreaSize.width - 5)),
                     4.0f + (rand() % (worldAreaSize.height - 5))};

        tile = worldArea->GetTile(static_cast<int>(position_.x),
                                  static_cast<int>(position_.y));
    }

    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) + 1};
}

void PLAYER::MOVE8NORTH()
{
    auto newX = position_.x;
    auto newY = position_.y - stepSize_;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) - 1};

    facingDirection_ = WorldDirections::North;
}

void PLAYER::MOVE8EAST()
{
    auto newX = position_.x + stepSize_;
    auto newY = position_.y;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x) + 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::East;
}

void PLAYER::MOVE8SOUTH()
{
    auto newX = position_.x;
    auto newY = position_.y + stepSize_;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) + 1};

    facingDirection_ = WorldDirections::South;
}

void PLAYER::MOVE8WEST()
{
    auto newX = position_.x - stepSize_;
    auto newY = position_.y;

    auto newTile = _<World>().currentWorldArea_->GetTile(
        {static_cast<int>(newX), static_cast<int>(newY)});

    if (newTile &&
        (newTile->ground_ == HASH("GroundWater") || newTile->creature_))
    {
        return;
    }

    position_ = {newX, newY};

    facedTileCoordinate_ = {static_cast<int>(position_.x) - 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::West;
}

void PLAYER::TURN8NORTH()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) - 1};

    facingDirection_ = WorldDirections::North;
}

void PLAYER::TURN8EAST()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x) + 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::East;
}

void PLAYER::TURN8SOUTH()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x),
                            static_cast<int>(position_.y) + 1};

    facingDirection_ = WorldDirections::South;
}

void PLAYER::TURN8WEST()
{
    facedTileCoordinate_ = {static_cast<int>(position_.x) - 1,
                            static_cast<int>(position_.y)};

    facingDirection_ = WorldDirections::West;
}

void PLAYER::ADD8EXPERIENCE(int amount)
{
    experience_ += amount;

    _<GUI8TEXT8CONSOLE>().PRINT8LINE("You gained " + std::to_string(amount) +
                                     " experience points.");
}

void PLAYER::HIT(float damage)
{
    health_ -= damage;

    ticksLastHitOnSelf_ = NOW();

    std::stringstream ssDamage;

    ssDamage << std::fixed << std::setprecision(1) << damage;

    _<GUI8TEXT8CONSOLE>().PRINT8LINE("You took " + ssDamage.str() + " damage.");
}