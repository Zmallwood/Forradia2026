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
    player::player()
    {
        spawn_on_suitable_location();
    }

    void player::spawn_on_suitable_location()
    {
        auto world_area{_<world>().current_world_area_};

        auto world_area_size{world_area->get_size()};

        position_ = {world_area_size.width / 2, world_area_size.height / 2};

        auto tile{world_area->get_tile(position_)};

        while (tile->ground_ == get_hash("ground_water"))
        {
            position_ = {rand() % world_area_size.width,
                         rand() % world_area_size.height};
            tile = world_area->get_tile(position_);
        }

        faced_tile_ = {position_.x, position_.y + 1};
    }

    void player::move_north()
    {
        auto new_x{position_.x};
        auto new_y{position_.y - 1};

        auto new_tile{_<world>().current_world_area_->get_tile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == get_hash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        faced_tile_ = {position_.x, position_.y - 1};

        facing_direction_ = world_directions::north;
    }

    void player::move_east()
    {
        auto new_x{position_.x + 1};
        auto new_y{position_.y};

        auto new_tile{_<world>().current_world_area_->get_tile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == get_hash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        faced_tile_ = {position_.x + 1, position_.y};

        facing_direction_ = world_directions::east;
    }

    void player::move_south()
    {
        auto new_x{position_.x};
        auto new_y{position_.y + 1};

        auto new_tile{_<world>().current_world_area_->get_tile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == get_hash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        faced_tile_ = {position_.x, position_.y + 1};

        facing_direction_ = world_directions::south;
    }

    void player::move_west()
    {
        auto new_x{position_.x - 1};
        auto new_y{position_.y};

        auto new_tile{_<world>().current_world_area_->get_tile({new_x, new_y})};

        if (new_tile && new_tile->ground_ == get_hash("ground_water"))
        {
            return;
        }

        position_ = {new_x, new_y};

        faced_tile_ = {position_.x - 1, position_.y};

        facing_direction_ = world_directions::west;
    }

    void player::turn_north()
    {
        faced_tile_ = {position_.x, position_.y - 1};

        facing_direction_ = world_directions::north;
    }

    void player::turn_east()
    {
        faced_tile_ = {position_.x + 1, position_.y};

        facing_direction_ = world_directions::east;
    }

    void player::turn_south()
    {
        faced_tile_ = {position_.x, position_.y + 1};

        facing_direction_ = world_directions::south;
    }

    void player::turn_west()
    {
        faced_tile_ = {position_.x - 1, position_.y};

        facing_direction_ = world_directions::west;
    }
}