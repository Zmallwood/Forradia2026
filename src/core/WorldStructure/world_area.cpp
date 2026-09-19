/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "world_area.hpp"
#include "Core/Configuration/game_properties.hpp"
#include "Core/WorldStructure/tile.hpp"

namespace Forradia
{
    world_area::world_area()
    {
        auto size{_<game_properties>().k_world_area_size_};

        for (auto x = 0; x < size.width; x++)
        {
            tiles_.push_back(std::vector<std::shared_ptr<tile>>());

            for (auto y = 0; y < size.height; y++)
            {
                tiles_.at(x).push_back(std::make_shared<tile>());
            }
        }
    }

    size world_area::get_size()
    {
        auto width{static_cast<int>(tiles_.size())};
        auto height{0};

        if (width)
        {
            height = static_cast<int>(tiles_.at(0).size());
        }

        return {width, height};
    }

    bool world_area::is_valid_coordinate(int x, int y)
    {
        auto size{get_size()};

        return x >= 0 && x < size.width && y >= 0 && y < size.height;
    }

    bool world_area::is_valid_coordinate(point coordinate)
    {
        return is_valid_coordinate(coordinate.x, coordinate.y);
    }

    std::shared_ptr<tile> world_area::get_tile(int x, int y)
    {
        if (is_valid_coordinate(x, y))
        {
            return tiles_.at(x).at(y);
        }

        return nullptr;
    }

    std::shared_ptr<tile> world_area::get_tile(point coordinate)
    {
        return get_tile(coordinate.x, coordinate.y);
    }
}