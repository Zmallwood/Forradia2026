/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "FirstPersonView.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "PositionedObject.hpp"

namespace Forradia
{
    void FirstPersonView::Render()
    {
        _<SDLDevice>().Clip(0.5f, 0.0f, 0.5f, 1.0f);

        auto view_width{GameProperties::k_viewWidth_};

        _<ColorRenderer>().FillRect(1.0f - view_width, 0.0f, view_width, 1.0f,
                                    Colors::k_black);

        std::string ground_image_name;

        auto world_area{_<World>().current_world_area_};
        auto faced_tile{world_area->GetTile(_<Player>().facedTile_)};

        if (!faced_tile)
        {
            return;
        }

        auto ground_type{faced_tile->ground_};

        switch (ground_type)
        {
        case GetHash("ground_grass"):
        {
            ground_image_name = "ground_first_person_grass";
            break;
        }
        case GetHash("ground_water"):
        {
            auto water_anim_index{(Ticks() % 450) / 150};

            ground_image_name =
                "ground_first_person_water_" + std::to_string(water_anim_index);

            break;
        }
        case GetHash("ground_dirt"):
        {
            ground_image_name = "ground_first_person_dirt";
            break;
        }
        case GetHash("ground_rock"):
        {
            ground_image_name = "ground_first_person_rock";
            break;
        }
        }

        _<ImageRenderer>().DrawImage(
            ground_image_name, 1.0f - view_width + k_margin_.x,
            0.75f + k_margin_.y, view_width - 2 * k_margin_.x,
            0.25f - 2 * k_margin_.y);

        auto tile_units_width{_<GameProperties>().k_tileUnitsWidth_};

        auto objects{faced_tile->tile_objects_->objects_};

        std::map<int, PositionedObject> objects_ordered;

        for (auto entry : objects)
        {
            auto position{entry.first};
            auto object{entry.second};

            int x_pos;
            int y_pos;

            auto facing_direction{_<Player>().facingDirection_};

            switch (facing_direction)
            {
            case WorldDirections::north:
                x_pos = position.x;
                y_pos = position.y;
                break;
            case WorldDirections::east:
                x_pos = position.y;
                y_pos = tile_units_width - 1 - position.x;
                break;
            case WorldDirections::south:
                x_pos = tile_units_width - 1 - position.x;
                y_pos = tile_units_width - 1 - position.y;
                break;
            case WorldDirections::west:
                x_pos = tile_units_width - 1 - position.y;
                y_pos = position.x;
                break;
            }

            PositionedObject positioned_object;
            positioned_object.position_ = {x_pos, y_pos};
            positioned_object.object_ = object;

            objects_ordered[y_pos] = positioned_object;
        }

        for (auto entry : objects_ordered)
        {
            auto x_pos = entry.second.position_.x;
            auto y_pos = entry.second.position_.y;
            auto object_type = entry.second.object_->type_;

            auto image_size{_<ImageBank>().GetImageSize(object_type)};

            constexpr float k_large_object_scale{0.22f};
            constexpr float k_small_object_scale{0.08f};

            float image_width;
            float image_height;

            auto is_small_object{_<ObjectIndex>().IsSmallObject(object_type)};

            if (is_small_object)
            {
                image_width = image_size.width / 60.0f * k_small_object_scale;
                image_height = image_size.height / 60.0f *
                               ConvertWidthToHeight(k_small_object_scale);
            }
            else
            {
                image_width = image_size.width / 60.0f * k_large_object_scale;
                image_height = image_size.height / 60.0f *
                               ConvertWidthToHeight(k_large_object_scale);
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

            _<ImageRenderer>().DrawImage(object_type, image_x, image_y,
                                         image_width, image_height);
        }

        constexpr float k_hand_scale{0.1f};

        auto hand_width{k_hand_scale};
        auto hand_height{ConvertWidthToHeight(k_hand_scale * 6 / 4)};
        auto hand_spacing{0.1f};

        auto left_hand_x{1.0f - view_width + 0.5f * view_width - hand_spacing -
                         hand_width / 2};
        auto right_hand_x{1.0f - view_width + 0.5f * view_width + hand_spacing -
                          hand_width / 2};

        auto ticks_last_movement{_<Player>().ticksLastMovement_};

        auto ticks_one_step{InvertSpeed(_<Player>().movementSpeed_)};

        auto delta{Ticks() - ticks_last_movement};

        auto hand_animation{0.0f};

        if (delta < ticks_one_step)
        {
            hand_animation =
                std::sin(static_cast<float>(delta) / ticks_one_step * M_PI) *
                0.02f;
        }

        auto hand_y_offset{0.07f};

        auto hand_y{1.0f - hand_height + hand_y_offset + hand_animation};

        _<ImageRenderer>().DrawImage("hand_left", left_hand_x, hand_y,
                                     hand_width, hand_height);
        _<ImageRenderer>().DrawImage("hand_right", right_hand_x, hand_y,
                                     hand_width, hand_height);

        _<ColorRenderer>().DrawLine(view_width, 0.0f, view_width, 1.0f,
                                    Colors::k_white);

        _<SDLDevice>().ResetClip();
    }
}