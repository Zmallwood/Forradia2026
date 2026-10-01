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
#include "Core/CoreGameObjects/PlayerEquipment.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "FirstPersonViewFunctions.hpp"

namespace Forradia
{
    void FirstPersonView::Render()
    {
        _<SDLDevice>().Clip(0.5f, 0.0f, 0.5f, 1.0f);

        auto viewWidth{GameProperties::k_viewWidth_};

        _<ColorRenderer>().FillRect(1.0f - viewWidth, 0.0f, viewWidth, 1.0f,
                                    Colors::k_black);

        auto now{Now()};

        std::string groundImageName;

        auto worldArea{_<World>().currentWorldArea_};
        auto facedTile{worldArea->GetTile(_<Player>().facedTileCoordinate_)};

        if (!facedTile)
        {
            return;
        }

        auto rightHandObject{_<Player>().playerEquipment_->rightHandObject_};
        auto leftHandObject{_<Player>().playerEquipment_->leftHandObject_};

        auto groundType{facedTile->ground_};

        switch (groundType)
        {
        case Hash("GroundGrass"):
        {
            groundImageName = "GroundFirstPersonGrass";
            break;
        }
        case Hash("GroundWater"):
        {
            auto water_anim_index{(Now() % 450) / 150};

            groundImageName =
                "GroundFirstPersonWater_" + std::to_string(water_anim_index);

            break;
        }
        case Hash("GroundDirt"):
        {
            groundImageName = "GroundFirstPersonDirt";
            break;
        }
        case Hash("GroundRock"):
        {
            groundImageName = "GroundFirstPersonRock";
            break;
        }
        }

        constexpr auto k_margin{GameProperties::k_firstPersonViewMargin_};

        _<ImageRenderer>().DrawImage(
            groundImageName, 1.0f - viewWidth + k_margin.x, 0.75f + k_margin.y,
            viewWidth - 2 * k_margin.x, 0.25f - 2 * k_margin.y);

        auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};

        auto orderedObjects{GetOrderedObjects()};

        constexpr auto largeObjectScale{GameProperties::k_largeObjectScale_};
        constexpr auto smallObjectScale{GameProperties::k_smallObjectScale_};

        for (auto entry : orderedObjects)
        {
            auto xPos{entry.second.position_.x};
            auto yPos{entry.second.position_.y};

            if (yPos * tileUnitsWidth + xPos >=
                tileUnitsWidth * tileUnitsWidth / 2)
            {
                break;
            }

            auto objectType = entry.second.object_->type_;

            auto imageSize{_<ImageBank>().GetImageSize(objectType)};

            float imageWidth;
            float imageHeight;

            auto isSmallObject{_<ObjectIndex>().IsSmallObject(objectType)};

            if (isSmallObject)
            {
                imageWidth = imageSize.width / 60.0f * smallObjectScale;
                imageHeight = imageSize.height / 60.0f *
                              ConvertWidthToHeight(smallObjectScale);
            }
            else
            {
                imageWidth = imageSize.width / 60.0f * largeObjectScale;
                imageHeight = imageSize.height / 60.0f *
                              ConvertWidthToHeight(largeObjectScale);
            }

            auto tileWidth{viewWidth - 2 * k_margin.x -
                           static_cast<float>(tileUnitsWidth - yPos) /
                               tileUnitsWidth * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + k_margin.x +
                          static_cast<float>(tileUnitsWidth - yPos) /
                              tileUnitsWidth * viewWidth * 0.3f};

            auto baseX{tileLeft +
                       static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
            auto baseY{0.75f + k_margin.y +
                       static_cast<float>(yPos + 1) / tileUnitsWidth *
                           (0.25f - 2 * k_margin.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            _<ImageRenderer>().DrawImage(objectType, imageX, imageY, imageWidth,
                                         imageHeight);

            auto impactObjects{_<ObjectIndex>().GetImpactObjects(objectType)};

            auto canImpact{false};

            for (auto impactObject : impactObjects)
            {
                if (rightHandObject)
                {
                    if (impactObject == rightHandObject->type_)
                    {
                        canImpact = true;
                        break;
                    }
                }

                if (leftHandObject)
                {
                    if (impactObject == leftHandObject->type_)
                    {
                        canImpact = true;
                        break;
                    }
                }
            }

            if (canImpact)
            {
                auto impactPoints{entry.second.object_->impactPoints_};

                for (auto impactPoint : impactPoints)
                {
                    auto impactPointWidth{GameProperties::k_impactPointWidth_};
                    auto impactPointHeight{
                        ConvertWidthToHeight(impactPointWidth)};
                    auto impactPointX{imageX +
                                      impactPoint.position.x * imageWidth -
                                      impactPointWidth / 2.0f};
                    auto impactPointY{imageY +
                                      impactPoint.position.y * imageHeight -
                                      impactPointHeight / 2.0f};

                    auto color{impactPoint.completed ? Colors::k_green
                                                     : Colors::k_red};

                    _<ColorRenderer>().FillRect(impactPointX, impactPointY,
                                                impactPointWidth,
                                                impactPointHeight, color);
                }
            }
        }

        auto creature{facedTile->creature_};

        if (creature)
        {
            auto creatureType{creature->type_};

            auto imageSize{_<ImageBank>().GetImageSize(creatureType)};

            auto imageWidth{imageSize.width / 60.0f * largeObjectScale};
            auto imageHeight{imageSize.height / 60.0f *
                             ConvertWidthToHeight(largeObjectScale)};

            auto tileWidth{viewWidth - 2 * k_margin.x -
                           0.5f * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + k_margin.x +
                          0.5f * viewWidth * 0.3f};

            auto baseX{tileLeft + 0.5f * tileWidth};
            auto baseY{0.75f + k_margin.y + 0.5f * (0.25f - 2 * k_margin.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            _<ImageRenderer>().DrawImage(creatureType, imageX, imageY,
                                         imageWidth, imageHeight);

            if (now - creature->ticksLastHitOnSelf_ < k_hitOtherEffectDuration_)
            {
                auto lastHitPosition{creature->lastHitPosition_};

                auto hitEffectImageSize{
                    _<ImageBank>().GetImageSize(Hash("HitEffect"))};

                constexpr float k_hitEffectScale{0.1f};

                auto hitEffectWidth{hitEffectImageSize.width / 60.0f *
                                    k_hitEffectScale};
                auto hitEffectHeight{hitEffectImageSize.height / 60.0f *
                                     ConvertWidthToHeight(k_hitEffectScale)};

                auto hitEffectBaseX{imageX + lastHitPosition.x * imageWidth};
                auto hitEffectBaseY{imageY + lastHitPosition.y * imageHeight};

                auto hitEffectX{hitEffectBaseX - hitEffectWidth / 2.0f};
                auto hitEffectY{hitEffectBaseY - hitEffectHeight / 2.0f};

                _<ImageRenderer>().DrawImage("HitEffect", hitEffectX,
                                             hitEffectY, hitEffectWidth,
                                             hitEffectHeight);
            }
        }

        for (auto entry : orderedObjects)
        {
            auto xPos{entry.second.position_.x};
            auto yPos{entry.second.position_.y};

            if (yPos * tileUnitsWidth + xPos <
                tileUnitsWidth * tileUnitsWidth / 2)
            {
                continue;
            }

            auto objectType = entry.second.object_->type_;

            auto imageSize{_<ImageBank>().GetImageSize(objectType)};

            float imageWidth;
            float imageHeight;

            auto isSmallObject{_<ObjectIndex>().IsSmallObject(objectType)};

            if (isSmallObject)
            {
                imageWidth = imageSize.width / 60.0f * smallObjectScale;
                imageHeight = imageSize.height / 60.0f *
                              ConvertWidthToHeight(smallObjectScale);
            }
            else
            {
                imageWidth = imageSize.width / 60.0f * largeObjectScale;
                imageHeight = imageSize.height / 60.0f *
                              ConvertWidthToHeight(largeObjectScale);
            }

            auto tileWidth{viewWidth - 2 * k_margin.x -
                           static_cast<float>(tileUnitsWidth - yPos) /
                               tileUnitsWidth * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + k_margin.x +
                          static_cast<float>(tileUnitsWidth - yPos) /
                              tileUnitsWidth * viewWidth * 0.3f};

            auto baseX{tileLeft +
                       static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
            auto baseY{0.75f + k_margin.y +
                       static_cast<float>(yPos + 1) / tileUnitsWidth *
                           (0.25f - 2 * k_margin.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            _<ImageRenderer>().DrawImage(objectType, imageX, imageY, imageWidth,
                                         imageHeight);

            auto impactObjects{_<ObjectIndex>().GetImpactObjects(objectType)};

            auto canImpact{false};

            for (auto impactObject : impactObjects)
            {
                if (rightHandObject)
                {
                    if (impactObject == rightHandObject->type_)
                    {
                        canImpact = true;
                        break;
                    }
                }

                if (leftHandObject)
                {
                    if (impactObject == leftHandObject->type_)
                    {
                        canImpact = true;
                        break;
                    }
                }
            }

            if (canImpact)
            {
                auto impactPoints{entry.second.object_->impactPoints_};

                for (auto impactPoint : impactPoints)
                {
                    auto impactPointWidth{GameProperties::k_impactPointWidth_};
                    auto impactPointHeight{
                        ConvertWidthToHeight(impactPointWidth)};
                    auto impactPointX{imageX +
                                      impactPoint.position.x * imageWidth -
                                      impactPointWidth / 2.0f};
                    auto impactPointY{imageY +
                                      impactPoint.position.y * imageHeight -
                                      impactPointHeight / 2.0f};

                    auto color{impactPoint.completed ? Colors::k_green
                                                     : Colors::k_red};

                    _<ColorRenderer>().FillRect(impactPointX, impactPointY,
                                                impactPointWidth,
                                                impactPointHeight, color);
                }
            }
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

        if (rightHandObject)
        {
            auto imageSize{_<ImageBank>().GetImageSize(rightHandObject->type_)};

            auto imageWidth{imageSize.width / 60.0f * k_wieldedObjectScale_};
            auto imageHeight{imageSize.height / 60.0f *
                             ConvertWidthToHeight(k_wieldedObjectScale_)};

            auto rightHandX{1.0f - viewWidth + 0.5f * viewWidth + handSpacing -
                            imageWidth / 2.0f};
            auto rightHandY{handY - imageHeight / 2.0f};

            _<ImageRenderer>().DrawImage(rightHandObject->type_, rightHandX,
                                         rightHandY, imageWidth, imageHeight);
        }

        if (leftHandObject)
        {
            auto imageSize{_<ImageBank>().GetImageSize(leftHandObject->type_)};

            auto imageWidth{imageSize.width / 60.0f * k_wieldedObjectScale_};
            auto imageHeight{imageSize.height / 60.0f *
                             ConvertWidthToHeight(k_wieldedObjectScale_)};

            auto leftHandX{1.0f - viewWidth + 0.5f * viewWidth - handSpacing -
                           imageWidth / 2.0f};
            auto leftHandY{handY - imageHeight / 2.0f};

            _<ImageRenderer>().DrawImage(leftHandObject->type_, leftHandX,
                                         leftHandY, imageWidth, imageHeight,
                                         true);
        }

        _<ImageRenderer>().DrawImage("HandLeft", leftHandX, handY, handWidth,
                                     handHeight);
        _<ImageRenderer>().DrawImage("HandRight", rightHandX, handY, handWidth,
                                     handHeight);

        _<ColorRenderer>().DrawLine(viewWidth, 0.0f, viewWidth, 1.0f,
                                    Colors::k_white);

        if (now < _<Player>().ticksLastHitOnSelf_ + k_hitSelfEffectDuration_)
        {
            _<ColorRenderer>().FillRect(viewWidth, 0.0f, viewWidth, 1.0f,
                                        Colors::k_red);
        }

        _<SDLDevice>().ResetClip();
    }
}