/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "tile_hovering.hpp"
#include "Core/Configuration/game_properties.hpp"
#include "Core/CoreGameObjects/player.hpp"
#include "Core/WorldStructure/tile.hpp"
#include "Core/WorldStructure/world.hpp"
#include "Core/WorldStructure/world_area.hpp"

namespace Forradia
{
    void tile_hovering::update()
    {
        auto mouse_position{get_mouse_position()};

        auto world_area{_<world>().current_world_area_};

        auto player_tile{world_area->get_tile(_<player>().position_)};

        if (!player_tile)
        {
            return;
        }

        auto player_elevation{player_tile->elevation_};

        auto tile_width{_<game_properties>().k_tile_width_};
        auto tile_height{convert_width_to_height(tile_width)};

        for (auto y = -6; y < 11 + 6; y++)
        {
            for (auto x = -6; x < 11 + 6; x++)
            {
                auto x_coordinate{_<player>().position_.x - 5 + x};
                auto y_coordinate{_<player>().position_.y - 5 + y};

                if (!world_area->is_valid_coordinate(x_coordinate,
                                                     y_coordinate))
                {
                    continue;
                }

                auto tile{world_area->get_tile(x_coordinate, y_coordinate)};

                auto elevation{tile->elevation_};

                auto tile_x{0.25f - tile_width / 2 + x * tile_width / 2 -
                            y * tile_width / 2};

                auto tile_y{0.5f - 5.5f * tile_height + x * tile_height / 2 +
                            y * tile_height / 2 +
                            player_elevation * tile_height / 4};

                auto center_bottom{
                    point_f{tile_x + tile_width / 2, tile_y + tile_height / 2}};

                auto dx_bottom{std::abs(mouse_position.x - center_bottom.x) /
                               (tile_width / 2)};
                auto dy_bottom{std::abs(mouse_position.y - center_bottom.y) /
                               (tile_height / 2)};
                if (dx_bottom + dy_bottom <= 1.0f)
                {
                    hovered_coordinate_ = point{x_coordinate, y_coordinate};
                }

                auto elevation_height{elevation * tile_height / 4};

                rect_f elevation_rect{
                    tile_x, tile_y - elevation_height + tile_height / 2,
                    tile_width, elevation_height};

                if (elevation_rect.contains(mouse_position))
                {
                    hovered_coordinate_ = point{x_coordinate, y_coordinate};
                }

                for (auto i = 0; i < elevation; i++)
                {
                    tile_y -= tile_height / 4;
                }

                auto center_top{
                    point_f{tile_x + tile_width / 2, tile_y + tile_height / 2}};

                auto dx_top{std::abs(mouse_position.x - center_top.x) /
                            (tile_width / 2)};
                auto dy_top{std::abs(mouse_position.y - center_top.y) /
                            (tile_height / 2)};
                if (dx_top + dy_top <= 1.0f)
                {
                    hovered_coordinate_ = point{x_coordinate, y_coordinate};
                }
            }
        }
    }
}