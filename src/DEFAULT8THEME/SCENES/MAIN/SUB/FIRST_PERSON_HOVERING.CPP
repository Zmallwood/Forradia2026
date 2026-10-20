// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/CREATURE8INDEX.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD_AREA.HPP"
#include "FIRST_PERSON_HOVERING.HPP"
#include "FIRST8PERSON8VIEW/FIRST_PERSON_VIEW_FUNCTIONS.HPP"

void FirstPersonHovering::Update()
{
    hoveredObject_ = nullptr;
    hoveredCreature_ = nullptr;

    auto viewWidth{GAME8PROPERTIES::k_viewWidth_};

    auto tileUnitsWidth{_<GAME8PROPERTIES>().k_tileUnitsWidth_};

    constexpr auto k_margin{GAME8PROPERTIES::k_firstPersonViewMargin_};

    auto orderedObjects{GetOrderedObjects()};

    auto mousePosition{GET8MOUSE8POSITION()};

    auto worldArea{_<World>().currentWorldArea_};
    auto facedTile{worldArea->GetTile(_<PLAYER>().facedTileCoordinate_)};

    if (!facedTile)
    {
        hoveredObject_ = nullptr;
        hoveredCreature_ = nullptr;

        return;
    }

    constexpr auto largeObjectScale{GAME8PROPERTIES::k_largeObjectScale_};
    constexpr auto smallObjectScale{GAME8PROPERTIES::k_smallObjectScale_};

    for (auto entry : orderedObjects)
    {
        auto xPos{entry.second.position_.x};
        auto yPos{entry.second.position_.y};

        if (yPos * tileUnitsWidth + xPos >= tileUnitsWidth * tileUnitsWidth / 2)
        {
            break;
        }

        auto objectType = entry.second.object_->type_;

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

        float imageWidth;
        float imageHeight;

        auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};
        if (isSmallObject)
        {
            imageWidth = imageSize.width / 60.0f * smallObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          CONVERT8WIDTH8TO8HEIGHT(
                              smallObjectScale *
                              (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                              tileUnitsWidth);
        }
        else
        {
            imageWidth = imageSize.width / 60.0f * largeObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          CONVERT8WIDTH8TO8HEIGHT(
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

        auto isHovered{_<IMAGE8BANK>().IS8PIXEL8VISIBLE(objectType, x, y)};

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

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType)};

        auto imageWidth{imageSize.width / 60.0f * largeObjectScale};
        auto imageHeight{imageSize.height / 60.0f *
                         CONVERT8WIDTH8TO8HEIGHT(largeObjectScale)};

        auto tileWidth{viewWidth - 2 * k_margin.x - 0.5f * viewWidth * 0.6f};
        auto tileLeft{1.0f - viewWidth + k_margin.x + 0.5f * viewWidth * 0.3f};

        auto baseX{tileLeft + 0.5f * tileWidth};
        auto baseY{0.75f + k_margin.y + 0.5f * (0.25f - 2 * k_margin.y)};

        auto imageX{baseX - imageWidth / 2.0f};
        auto imageY{baseY - imageHeight};

        auto scale{largeObjectScale};

        auto x{(mousePosition.x - imageX) / imageWidth};
        auto y{(mousePosition.y - imageY) / imageHeight};

        auto isHovered{_<IMAGE8BANK>().IS8PIXEL8VISIBLE(creatureType, x, y)};

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

        if (yPos * tileUnitsWidth + xPos < tileUnitsWidth * tileUnitsWidth / 2)
        {
            continue;
        }

        auto objectType = entry.second.object_->type_;

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

        float imageWidth;
        float imageHeight;

        auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};

        if (isSmallObject)
        {
            imageWidth = imageSize.width / 60.0f * smallObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          CONVERT8WIDTH8TO8HEIGHT(
                              smallObjectScale *
                              (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                              tileUnitsWidth);
        }
        else
        {
            imageWidth = imageSize.width / 60.0f * largeObjectScale *
                         (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                         tileUnitsWidth;
            imageHeight = imageSize.height / 60.0f *
                          CONVERT8WIDTH8TO8HEIGHT(
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

        auto isHovered{_<IMAGE8BANK>().IS8PIXEL8VISIBLE(objectType, x, y)};

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
    auto mousePosition{GET8MOUSE8POSITION()};

    if (hoveredObject_)
    {
        auto objectLabel{
            _<OBJECT8INDEX>().GET8OBJECT8LABEL(hoveredObject_->type_)};

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
            _<CREATURE8INDEX>().GET8CREATURE8LABEL(hoveredCreature_->type_)};

        if (creatureLabel.empty())
        {
            creatureLabel = "?";
        }

        _<TextRenderer>().DrawString(creatureLabel, mousePosition.x,
                                     mousePosition.y + k_textYOffset_);
    }
}