/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "world_view.hpp"
#include "Core/Assets/image_bank.hpp"
#include "Core/Configuration/game_properties.hpp"
#include "Core/Configuration/object_index.hpp"
#include "Core/CoreGameObjects/player.hpp"
#include "Core/Rendering/Colors/color_renderer.hpp"
#include "Core/Rendering/Images/image_renderer.hpp"
#include "Core/SDLDevice/sdl_device.hpp"
#include "Core/WorldStructure/object.hpp"
#include "Core/WorldStructure/tile.hpp"
#include "Core/WorldStructure/tile_objects.hpp"
#include "Core/WorldStructure/world.hpp"
#include "Core/WorldStructure/world_area.hpp"
#include "Theme/Scenes/Main/Sub/tile_hovering.hpp"

namespace Forradia
{
    void world_view::render()
    {
        _<sdl_device>().clip(0.0f, 0.0f, 0.5f, 1.0f);

        auto view_width{game_properties::k_view_width_};

        _<color_renderer>().fill_rect(0.0f, 0.0f, view_width, 1.0f,
                                      colors::k_black);

        auto world_area{_<world>().current_world_area_};

        auto player_tile{world_area->get_tile(_<player>().position_)};

        auto player_elevation{0};

        if (player_tile)
        {
            player_elevation = player_tile->elevation_;
        }

        auto hovered_coordinate{_<tile_hovering>().hovered_coordinate_};

        auto faced_tile{_<player>().faced_tile_};

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

                auto num_blocking_objects{0};

                auto dx{_<player>().position_.x - x_coordinate};
                auto dy{_<player>().position_.y - y_coordinate};

                if (dx != 0 || dy != 0)
                {
                    auto num_steps{std::max(std::abs(dx), std::abs(dy))};

                    auto step_x{static_cast<float>(dx) / num_steps};
                    auto step_y{static_cast<float>(dy) / num_steps};

                    auto current_x_f{static_cast<float>(x_coordinate) + step_x};
                    auto current_y_f{static_cast<float>(y_coordinate) + step_y};

                    for (auto i = 0; i < num_steps - 1; i++)
                    {
                        auto current_x{static_cast<int>(current_x_f)};
                        auto current_y{static_cast<int>(current_y_f)};

                        auto tile{world_area->get_tile(current_x, current_y)};

                        if (!tile)
                        {
                            continue;
                        }

                        for (auto object : tile->tile_objects_->objects_)
                        {
                            if (!_<object_index>().is_small_object(
                                    object.second->type_))
                            {
                                num_blocking_objects++;

                                break;
                            }
                        }

                        current_x_f += step_x;
                        current_y_f += step_y;
                    }

                    if (num_blocking_objects >= 2)
                    {
                        continue;
                    }
                }

                auto tile{world_area->get_tile(x_coordinate, y_coordinate)};

                auto elevation{tile->elevation_};

                point coordinate_north{x_coordinate, y_coordinate - 1};
                point coordinate_east{x_coordinate + 1, y_coordinate};
                point coordinate_south{x_coordinate, y_coordinate + 1};
                point coordinate_west{x_coordinate - 1, y_coordinate};

                auto elevation_north{elevation};
                auto elevation_east{elevation};
                auto elevation_south{elevation};
                auto elevation_west{elevation};

                if (world_area->is_valid_coordinate(coordinate_north))
                {
                    elevation_north =
                        world_area->get_tile(coordinate_north)->elevation_;
                }

                if (world_area->is_valid_coordinate(coordinate_east))
                {
                    elevation_east =
                        world_area->get_tile(coordinate_east)->elevation_;
                }

                if (world_area->is_valid_coordinate(coordinate_south))
                {
                    elevation_south =
                        world_area->get_tile(coordinate_south)->elevation_;
                }

                if (world_area->is_valid_coordinate(coordinate_west))
                {
                    elevation_west =
                        world_area->get_tile(coordinate_west)->elevation_;
                }

                auto tile_x{0.25f - tile_width / 2 + x * tile_width / 2 -
                            y * tile_width / 2};

                auto tile_y{0.5f - 5.5f * tile_height + x * tile_height / 2 +
                            y * tile_height / 2 +
                            player_elevation * tile_height / 4};

                for (auto i = 0; i < elevation; i++)
                {
                    _<image_renderer>().draw_image(
                        "elevation", tile_x, tile_y + tile_height / 4,
                        tile_width, tile_height * 3 / 4);

                    tile_y -= tile_height / 4;
                }

                auto ground{tile->ground_};

                if (ground == get_hash("ground_water"))
                {
                    auto water_anim_index{
                        ((ticks() + 10 * x_coordinate * y_coordinate) % 900) /
                        300};

                    std::string ground_image_name{
                        "ground_water_" + std::to_string(water_anim_index)};

                    ground = get_hash(ground_image_name);
                }

                _<image_renderer>().draw_image(ground, tile_x, tile_y,
                                               tile_width + k_small_value,
                                               tile_height + k_small_value);

                if (elevation > elevation_north)
                {
                    _<image_renderer>().draw_image("elevation_edge_north",
                                                   tile_x, tile_y, tile_width,
                                                   tile_height);
                }

                if (elevation > elevation_east)
                {
                    _<image_renderer>().draw_image("elevation_edge_east",
                                                   tile_x, tile_y, tile_width,
                                                   tile_height);
                }

                if (elevation > elevation_south)
                {
                    _<image_renderer>().draw_image("elevation_edge_south",
                                                   tile_x, tile_y, tile_width,
                                                   tile_height);
                }

                if (elevation > elevation_west)
                {
                    _<image_renderer>().draw_image("elevation_edge_west",
                                                   tile_x, tile_y, tile_width,
                                                   tile_height);
                }

                if (x_coordinate == faced_tile.x &&
                    y_coordinate == faced_tile.y)
                {
                    _<image_renderer>().draw_image("faced_tile", tile_x, tile_y,
                                                   tile_width, tile_height);
                }

                if (x_coordinate == hovered_coordinate.x &&
                    y_coordinate == hovered_coordinate.y)
                {

                    _<image_renderer>().draw_image("hovered_tile", tile_x,
                                                   tile_y, tile_width,
                                                   tile_height);
                }

                auto objects{tile->tile_objects_->objects_};

                for (auto entry : objects)
                {
                    auto object{entry.second};

                    auto object_type{object->type_};

                    auto is_small_object{
                        _<object_index>().is_small_object(object_type)};

                    if (is_small_object)
                    {
                        continue;
                    }

                    auto image_size{
                        _<image_bank>().get_image_size(object_type)};

                    auto object_width{image_size.width / 60.0f * tile_width};
                    auto object_height{image_size.height / 60.0f * tile_height};

                    auto object_x{tile_x + tile_width / 2 - object_width / 2};
                    auto object_y{tile_y + tile_height / 2 - object_height};

                    _<image_renderer>().draw_image(object_type, object_x,
                                                   object_y, object_width,
                                                   object_height);
                }

                if (x_coordinate == _<player>().position_.x &&
                    y_coordinate == _<player>().position_.y)
                {
                    _<image_renderer>().draw_image("player", tile_x,
                                                   tile_y - tile_height / 2,
                                                   tile_width, tile_height);
                }
            }
        }
        _<sdl_device>().reset_clip();
    }
}