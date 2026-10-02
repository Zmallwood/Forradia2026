/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "FirstPersonHovering.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/CreatureIndex.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Core/WorldStructure/Creature.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "FirstPersonView/FirstPersonViewFunctions.hpp"

namespace Forradia
{
    void FirstPersonHovering::Update()
    {
        hoveredObject_ = nullptr;
        hoveredCreature_ = nullptr;

        auto viewWidth{GameProperties::k_viewWidth_};

        auto tileUnitsWidth{_<GameProperties>().k_tileUnitsWidth_};

        constexpr auto k_margin{GameProperties::k_firstPersonViewMargin_};

        auto orderedObjects{GetOrderedObjects()};

        auto mousePosition{GetMousePosition()};

        auto worldArea{_<World>().currentWorldArea_};
        auto facedTile{worldArea->GetTile(_<Player>().facedTileCoordinate_)};

        if (!facedTile)
        {
            hoveredObject_ = nullptr;
            hoveredCreature_ = nullptr;

            return;
        }

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
                imageWidth = imageSize.width / 60.0f * smallObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    ConvertWidthToHeight(
                        smallObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            }
            else
            {
                imageWidth = imageSize.width / 60.0f * largeObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    ConvertWidthToHeight(
                        largeObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
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

            auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

            auto x{(mousePosition.x - imageX) / imageWidth};
            auto y{(mousePosition.y - imageY) / imageHeight};

            auto isHovered{_<ImageBank>().IsPixelVisible(objectType, x, y)};

            if (isHovered)
            {
                hoveredObject_ = entry.second.object_;

                hoveredCreature_ = nullptr;

                hoveredThingMouseOffset_ = {mousePosition.x - baseX,
                                            mousePosition.y - baseY};
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

            auto scale{largeObjectScale};

            auto x{(mousePosition.x - imageX) / imageWidth};
            auto y{(mousePosition.y - imageY) / imageHeight};

            auto isHovered{_<ImageBank>().IsPixelVisible(creatureType, x, y)};

            if (isHovered)
            {
                hoveredObject_ = nullptr;

                hoveredCreature_ = creature;

                hoveredThingMouseOffset_ = {mousePosition.x - baseX,
                                            mousePosition.y - baseY};
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
                imageWidth = imageSize.width / 60.0f * smallObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    ConvertWidthToHeight(
                        smallObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            }
            else
            {
                imageWidth = imageSize.width / 60.0f * largeObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    ConvertWidthToHeight(
                        largeObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
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

            auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

            auto x{(mousePosition.x - imageX) / imageWidth};
            auto y{(mousePosition.y - imageY) / imageHeight};

            auto isHovered{_<ImageBank>().IsPixelVisible(objectType, x, y)};

            if (isHovered)
            {
                hoveredObject_ = entry.second.object_;

                hoveredCreature_ = nullptr;

                hoveredThingMouseOffset_ = {mousePosition.x - baseX,
                                            mousePosition.y - baseY};
            }
        }
    }

    void FirstPersonHovering::Render()
    {
        auto mousePosition{GetMousePosition()};

        if (hoveredObject_)
        {
            auto objectLabel{
                _<ObjectIndex>().GetObjectLabel(hoveredObject_->type_)};

            if (objectLabel.empty())
            {
                objectLabel = "?";
            }

            _<TextRenderer>().DrawString(objectLabel, mousePosition.x,
                                         mousePosition.y + k_textYOffset_);
        }
        else if (hoveredCreature_)
        {
            auto creatureLabel{
                _<CreatureIndex>().GetCreatureLabel(hoveredCreature_->type_)};

            if (creatureLabel.empty())
            {
                creatureLabel = "?";
            }

            _<TextRenderer>().DrawString(creatureLabel, mousePosition.x,
                                         mousePosition.y + k_textYOffset_);
        }
    }
}