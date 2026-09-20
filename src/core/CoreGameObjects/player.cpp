/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "Player.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    Player::Player()
    {
        SpawnOnSuitableLocation();
    }

    void Player::SpawnOnSuitableLocation()
    {
        auto world_area{_<World>().current_world_area_};

        auto world_area_size{world_area->GetSize()};

        position_ = {world_area_size.width / 2, world_area_size.height / 2};

        auto tile{world_area->GetTile(position_)};

        while (tile->ground_ == GetHash("ground_water"))
        {
            position_ = {rand() % world_area_size.width,
                         rand() % world_area_size.height};
            tile = world_area->GetTile(position_);
        }

        facedTile_ = {position_.x, position_.y + 1};
    }

    void Player::MoveNorth()
    {
        auto new_x{position_.x};
        auto new_y{position_.y - 1};

        auto new_tile{_<World>().current_world_area_->GetTile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == GetHash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        facedTile_ = {position_.x, position_.y - 1};

        facingDirection_ = WorldDirections::north;
    }

    void Player::MoveEast()
    {
        auto new_x{position_.x + 1};
        auto new_y{position_.y};

        auto new_tile{_<World>().current_world_area_->GetTile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == GetHash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        facedTile_ = {position_.x + 1, position_.y};

        facingDirection_ = WorldDirections::east;
    }

    void Player::MoveSouth()
    {
        auto new_x{position_.x};
        auto new_y{position_.y + 1};

        auto new_tile{_<World>().current_world_area_->GetTile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == GetHash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        facedTile_ = {position_.x, position_.y + 1};

        facingDirection_ = WorldDirections::south;
    }

    void Player::MoveWest()
    {
        auto new_x{position_.x - 1};
        auto new_y{position_.y};

        auto new_tile{_<World>().current_world_area_->GetTile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == GetHash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        facedTile_ = {position_.x - 1, position_.y};

        facingDirection_ = WorldDirections::west;
    }

    void Player::TurnNorth()
    {
        facedTile_ = {position_.x, position_.y - 1};

        facingDirection_ = WorldDirections::north;
    }

    void Player::TurnEast()
    {
        facedTile_ = {position_.x + 1, position_.y};

        facingDirection_ = WorldDirections::east;
    }

    void Player::TurnSouth()
    {
        facedTile_ = {position_.x, position_.y + 1};

        facingDirection_ = WorldDirections::south;
    }

    void Player::TurnWest()
    {
        facedTile_ = {position_.x - 1, position_.y};

        facingDirection_ = WorldDirections::west;
    }
}