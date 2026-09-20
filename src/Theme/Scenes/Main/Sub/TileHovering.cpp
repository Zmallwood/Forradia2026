/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "TileHovering.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"

namespace Forradia
{
    void TileHovering::Update()
    {
        auto mouse_position{GetMousePosition()};

        auto world_area{_<World>().current_world_area_};

        auto player_tile{world_area->GetTile(_<Player>().position_)};

        if (!player_tile)
        {
            return;
        }

        auto player_elevation{player_tile->elevation_};

        auto tile_width{GameProperties::k_tileWidth_};
        auto tile_height{ConvertWidthToHeight(tile_width)};

        for (auto y = -6; y < 11 + 6; y++)
        {
            for (auto x = -6; x < 11 + 6; x++)
            {
                auto x_coordinate{_<Player>().position_.x - 5 + x};
                auto y_coordinate{_<Player>().position_.y - 5 + y};

                if (!world_area->IsValidCoordinate(x_coordinate, y_coordinate))
                {
                    continue;
                }

                auto tile{world_area->GetTile(x_coordinate, y_coordinate)};

                auto elevation{tile->elevation_};

                auto tile_x{0.25f - tile_width / 2 + x * tile_width / 2 -
                            y * tile_width / 2};

                auto tile_y{0.5f - 5.5f * tile_height + x * tile_height / 2 +
                            y * tile_height / 2 +
                            player_elevation * tile_height / 4};

                auto center_bottom{
                    PointF{tile_x + tile_width / 2, tile_y + tile_height / 2}};

                auto dx_bottom{std::abs(mouse_position.x - center_bottom.x) /
                               (tile_width / 2)};
                auto dy_bottom{std::abs(mouse_position.y - center_bottom.y) /
                               (tile_height / 2)};
                if (dx_bottom + dy_bottom <= 1.0f)
                {
                    hovered_coordinate_ = Point{x_coordinate, y_coordinate};
                }

                auto elevation_height{elevation * tile_height / 4};

                RectF elevation_rect{
                    tile_x, tile_y - elevation_height + tile_height / 2,
                    tile_width, elevation_height};

                if (elevation_rect.Contains(mouse_position))
                {
                    hovered_coordinate_ = Point{x_coordinate, y_coordinate};
                }

                for (auto i = 0; i < elevation; i++)
                {
                    tile_y -= tile_height / 4;
                }

                auto center_top{
                    PointF{tile_x + tile_width / 2, tile_y + tile_height / 2}};

                auto dx_top{std::abs(mouse_position.x - center_top.x) /
                            (tile_width / 2)};
                auto dy_top{std::abs(mouse_position.y - center_top.y) /
                            (tile_height / 2)};
                if (dx_top + dy_top <= 1.0f)
                {
                    hovered_coordinate_ = Point{x_coordinate, y_coordinate};
                }
            }
        }
    }
}