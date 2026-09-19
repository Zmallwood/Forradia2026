/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "first_person_view.hpp"
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
#include "positioned_object.hpp"

namespace Forradia
{
    void first_person_view::render()
    {
        _<sdl_device>().clip(0.5f, 0.0f, 0.5f, 1.0f);

        auto view_width{game_properties::k_view_width_};

        _<color_renderer>().fill_rect(1.0f - view_width, 0.0f, view_width, 1.0f,
                                      colors::k_black);

        std::string ground_image_name;

        auto world_area{_<world>().current_world_area_};
        auto faced_tile{world_area->get_tile(_<player>().faced_tile_)};

        if (!faced_tile)
        {
            return;
        }

        auto ground_type{faced_tile->ground_};

        switch (ground_type)
        {
        case get_hash("ground_grass"):
        {
            ground_image_name = "ground_first_person_grass";
            break;
        }
        case get_hash("ground_water"):
        {
            auto water_anim_index{(ticks() % 450) / 150};

            ground_image_name =
                "ground_first_person_water_" + std::to_string(water_anim_index);

            break;
        }
        case get_hash("ground_dirt"):
        {
            ground_image_name = "ground_first_person_dirt";
            break;
        }
        case get_hash("ground_rock"):
        {
            ground_image_name = "ground_first_person_rock";
            break;
        }
        }

        _<image_renderer>().draw_image(
            ground_image_name, 1.0f - view_width + k_margin_.x,
            0.75f + k_margin_.y, view_width - 2 * k_margin_.x,
            0.25f - 2 * k_margin_.y);

        auto tile_units_width{_<game_properties>().k_tile_units_width_};

        auto objects{faced_tile->tile_objects_->objects_};

        std::map<int, positioned_object> objects_ordered;

        for (auto entry : objects)
        {
            auto position{entry.first};
            auto object{entry.second};

            int x_pos;
            int y_pos;

            auto facing_direction{_<player>().facing_direction_};

            switch (facing_direction)
            {
            case world_directions::north:
                x_pos = position.x;
                y_pos = position.y;
                break;
            case world_directions::east:
                x_pos = position.y;
                y_pos = tile_units_width - 1 - position.x;
                break;
            case world_directions::south:
                x_pos = tile_units_width - 1 - position.x;
                y_pos = tile_units_width - 1 - position.y;
                break;
            case world_directions::west:
                x_pos = tile_units_width - 1 - position.y;
                y_pos = position.x;
                break;
            }

            positioned_object positioned_object;
            positioned_object.position_ = {x_pos, y_pos};
            positioned_object.object_ = object;

            objects_ordered[y_pos] = positioned_object;
        }

        for (auto entry : objects_ordered)
        {
            auto x_pos = entry.second.position_.x;
            auto y_pos = entry.second.position_.y;
            auto object_type = entry.second.object_->type_;

            auto image_size{_<image_bank>().get_image_size(object_type)};

            constexpr float k_large_object_scale{0.22f};
            constexpr float k_small_object_scale{0.08f};

            float image_width;
            float image_height;

            auto is_small_object{
                _<object_index>().is_small_object(object_type)};

            if (is_small_object)
            {
                image_width = image_size.width / 60.0f * k_small_object_scale;
                image_height = image_size.height / 60.0f *
                               convert_width_to_height(k_small_object_scale);
            }
            else
            {
                image_width = image_size.width / 60.0f * k_large_object_scale;
                image_height = image_size.height / 60.0f *
                               convert_width_to_height(k_large_object_scale);
            }

            auto tile_width{view_width - 2 * k_margin_.x -
                            static_cast<float>(tile_units_width - y_pos) /
                                tile_units_width * view_width * 0.6f};
            auto tile_left{1.0f - view_width + k_margin_.x +
                           static_cast<float>(tile_units_width - y_pos) /
                               tile_units_width * view_width * 0.3f};

            auto base_x{tile_left + static_cast<float>(x_pos) /
                                        tile_units_width * tile_width};
            auto base_y{0.75f + k_margin_.y +
                        static_cast<float>(y_pos + 1) / tile_units_width *
                            (0.25f - 2 * k_margin_.y)};

            auto image_x{base_x - image_width / 2.0f};
            auto image_y{base_y - image_height};

            _<image_renderer>().draw_image(object_type, image_x, image_y,
                                           image_width, image_height);
        }

        constexpr float k_hand_scale{0.1f};

        auto hand_width{k_hand_scale};
        auto hand_height{convert_width_to_height(k_hand_scale * 6 / 4)};
        auto hand_spacing{0.1f};

        auto left_hand_x{1.0f - view_width + 0.5f * view_width - hand_spacing -
                         hand_width / 2};
        auto right_hand_x{1.0f - view_width + 0.5f * view_width + hand_spacing -
                          hand_width / 2};

        auto ticks_last_movement{_<player>().ticks_last_movement_};

        auto ticks_one_step{invert_speed(_<player>().movement_speed_)};

        auto delta{ticks() - ticks_last_movement};

        auto hand_animation{0.0f};

        if (delta < ticks_one_step)
        {
            hand_animation =
                std::sin(static_cast<float>(delta) / ticks_one_step * M_PI) *
                0.02f;
        }

        auto hand_y_offset{0.07f};

        auto hand_y{1.0f - hand_height + hand_y_offset + hand_animation};

        _<image_renderer>().draw_image("hand_left", left_hand_x, hand_y,
                                       hand_width, hand_height);
        _<image_renderer>().draw_image("hand_right", right_hand_x, hand_y,
                                       hand_width, hand_height);

        _<color_renderer>().draw_line(view_width, 0.0f, view_width, 1.0f,
                                      colors::k_white);

        _<sdl_device>().reset_clip();
    }
}