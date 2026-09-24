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
        auto worldArea{_<World>().currentWorldArea_};

        auto worldAreaSize{worldArea->GetSize()};

        position_ = {worldAreaSize.width / 2, worldAreaSize.height / 2};

        auto tile{worldArea->GetTile(position_)};

        while (tile->ground_ == Hash("ground_water"))
        {
            position_ = {rand() % worldAreaSize.width,
                         rand() % worldAreaSize.height};
            tile = worldArea->GetTile(position_);
        }

        facedTile_ = {position_.x, position_.y + 1};
    }

    void Player::MoveNorth()
    {
        auto newX{position_.x};
        auto newY{position_.y - 1};

        auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

        if (newTile && newTile->ground_ == Hash("ground_water"))
        {
            return;
        }

        position_ = {newX, newY};

        facedTile_ = {position_.x, position_.y - 1};

        facingDirection_ = WorldDirections::North;
    }

    void Player::MoveEast()
    {
        auto newX{position_.x + 1};
        auto newY{position_.y};

        auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

        if (newTile && newTile->ground_ == Hash("ground_water"))
        {
            return;
        }

        position_ = {newX, newY};

        facedTile_ = {position_.x + 1, position_.y};

        facingDirection_ = WorldDirections::East;
    }

    void Player::MoveSouth()
    {
        auto newX{position_.x};
        auto newY{position_.y + 1};

        auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

        if (newTile && newTile->ground_ == Hash("ground_water"))
        {
            return;
        }

        position_ = {newX, newY};

        facedTile_ = {position_.x, position_.y + 1};

        facingDirection_ = WorldDirections::South;
    }

    void Player::MoveWest()
    {
        auto newX{position_.x - 1};
        auto newY{position_.y};

        auto newTile{_<World>().currentWorldArea_->GetTile({newX, newY})};

        if (newTile && newTile->ground_ == Hash("ground_water"))
        {
            return;
        }

        position_ = {newX, newY};

        facedTile_ = {position_.x - 1, position_.y};

        facingDirection_ = WorldDirections::West;
    }

    void Player::TurnNorth()
    {
        facedTile_ = {position_.x, position_.y - 1};

        facingDirection_ = WorldDirections::North;
    }

    void Player::TurnEast()
    {
        facedTile_ = {position_.x + 1, position_.y};

        facingDirection_ = WorldDirections::East;
    }

    void Player::TurnSouth()
    {
        facedTile_ = {position_.x, position_.y + 1};

        facingDirection_ = WorldDirections::South;
    }

    void Player::TurnWest()
    {
        facedTile_ = {position_.x - 1, position_.y};

        facingDirection_ = WorldDirections::West;
    }
}