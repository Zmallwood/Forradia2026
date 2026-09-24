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

        auto viewWidth{GameProperties::k_viewWidth_};

        _<ColorRenderer>().FillRect(1.0f - viewWidth, 0.0f, viewWidth, 1.0f,
                                    Colors::k_black);

        std::string groundImageName;

        auto worldArea{_<World>().currentWorldArea_};
        auto facedTile{worldArea->GetTile(_<Player>().facedTile_)};

        if (!facedTile)
        {
            return;
        }

        auto groundType{facedTile->ground_};

        switch (groundType)
        {
        case Hash("ground_grass"):
        {
            groundImageName = "ground_first_person_grass";
            break;
        }
        case Hash("ground_water"):
        {
            auto water_anim_index{(Now() % 450) / 150};

            groundImageName =
                "ground_first_person_water_" + std::to_string(water_anim_index);

            break;
        }
        case Hash("ground_dirt"):
        {
            groundImageName = "ground_first_person_dirt";
            break;
        }
        case Hash("ground_rock"):
        {
            groundImageName = "ground_first_person_rock";
            break;
        }
        }

        _<ImageRenderer>().DrawImage(
            groundImageName, 1.0f - viewWidth + k_margin_.x,
            0.75f + k_margin_.y, viewWidth - 2 * k_margin_.x,
            0.25f - 2 * k_margin_.y);

        auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};

        auto objects{facedTile->tileObjects_->objects_};

        std::map<int, PositionedObject> objectsOrdered;

        for (auto entry : objects)
        {
            auto position{entry.first};
            auto object{entry.second};

            int xPos;
            int yPos;

            auto facingDirection{_<Player>().facingDirection_};

            switch (facingDirection)
            {
            case WorldDirections::North:
                xPos = position.x;
                yPos = position.y;
                break;
            case WorldDirections::East:
                xPos = position.y;
                yPos = tileUnitsWidth - 1 - position.x;
                break;
            case WorldDirections::South:
                xPos = tileUnitsWidth - 1 - position.x;
                yPos = tileUnitsWidth - 1 - position.y;
                break;
            case WorldDirections::West:
                xPos = tileUnitsWidth - 1 - position.y;
                yPos = position.x;
                break;
            }

            PositionedObject positionedObject;
            positionedObject.position_ = {xPos, yPos};
            positionedObject.object_ = object;

            objectsOrdered[yPos] = positionedObject;
        }

        for (auto entry : objectsOrdered)
        {
            auto xPos = entry.second.position_.x;
            auto yPos = entry.second.position_.y;
            auto objectType = entry.second.object_->type_;

            auto imageSize{_<ImageBank>().GetImageSize(objectType)};

            constexpr float k_largeObjectScale{0.22f};
            constexpr float k_smallObjectScale{0.08f};

            float imageWidth;
            float imageHeight;

            auto isSmallObject{_<ObjectIndex>().IsSmallObject(objectType)};

            if (isSmallObject)
            {
                imageWidth = imageSize.width / 60.0f * k_smallObjectScale;
                imageHeight = imageSize.height / 60.0f *
                              ConvertWidthToHeight(k_smallObjectScale);
            }
            else
            {
                imageWidth = imageSize.width / 60.0f * k_largeObjectScale;
                imageHeight = imageSize.height / 60.0f *
                              ConvertWidthToHeight(k_largeObjectScale);
            }

            auto tileWidth{viewWidth - 2 * k_margin_.x -
                           static_cast<float>(tileUnitsWidth - yPos) /
                               tileUnitsWidth * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + k_margin_.x +
                          static_cast<float>(tileUnitsWidth - yPos) /
                              tileUnitsWidth * viewWidth * 0.3f};

            auto baseX{tileLeft +
                       static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
            auto baseY{0.75f + k_margin_.y +
                       static_cast<float>(yPos + 1) / tileUnitsWidth *
                           (0.25f - 2 * k_margin_.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            _<ImageRenderer>().DrawImage(objectType, imageX, imageY, imageWidth,
                                         imageHeight);
        }

        constexpr float k_handScale{0.1f};

        auto handWidth{k_handScale};
        auto handHeight{ConvertWidthToHeight(k_handScale * 6 / 4)};
        auto handSpacing{0.1f};

        auto leftHandX{1.0f - viewWidth + 0.5f * viewWidth - handSpacing -
                       handWidth / 2};
        auto rightHandX{1.0f - viewWidth + 0.5f * viewWidth + handSpacing -
                        handWidth / 2};

        auto ticksLastMovement{_<Player>().ticksLastMovement_};

        auto ticksOneStep{InvertSpeed(_<Player>().movementSpeed_)};

        auto delta{Now() - ticksLastMovement};

        auto handAnimation{0.0f};

        if (delta < ticksOneStep)
        {
            handAnimation =
                std::sin(static_cast<float>(delta) / ticksOneStep * M_PI) *
                0.02f;
        }

        auto handYOffset{0.07f};

        auto handY{1.0f - handHeight + handYOffset + handAnimation};

        _<ImageRenderer>().DrawImage("hand_left", leftHandX, handY, handWidth,
                                     handHeight);
        _<ImageRenderer>().DrawImage("hand_right", rightHandX, handY, handWidth,
                                     handHeight);

        _<ColorRenderer>().DrawLine(viewWidth, 0.0f, viewWidth, 1.0f,
                                    Colors::k_white);

        _<SDLDevice>().ResetClip();
    }
}