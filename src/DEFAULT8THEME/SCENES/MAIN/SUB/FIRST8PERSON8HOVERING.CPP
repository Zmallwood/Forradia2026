//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "FIRST8PERSON8HOVERING.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/CREATURE8INDEX.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/CREATURE.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "FIRST8PERSON8VIEW/FIRST8PERSON8VIEW8FUNCTIONS.HPP"

namespace FORRADIA8GAME {
    void
    FIRST8PERSON8HOVERING::UPDATE() {
        hoveredObject_ = nullptr;
        hoveredCreature_ = nullptr;

        auto viewWidth{GAME8PROPERTIES::kViewWidth_};

        auto tileUnitsWidth{_<GAME8PROPERTIES>().kTileUnitsWidth_};

        constexpr auto kMargin{GAME8PROPERTIES::kFirstPersonViewMargin_};

        auto orderedObjects{GET8ORDERED8OBJECTS()};

        auto mousePosition{GET8MOUSE8POSITION()};

        auto worldArea{_<WORLD>().currentWorldArea_};
        auto facedTile{worldArea->GET8TILE(_<PLAYER>().facedTileCoordinate_)};

        if (!facedTile) {
            hoveredObject_ = nullptr;
            hoveredCreature_ = nullptr;

            return;
        }

        constexpr auto largeObjectScale{GAME8PROPERTIES::kLargeObjectScale_};
        constexpr auto smallObjectScale{GAME8PROPERTIES::kSmallObjectScale_};

        for (auto entry : orderedObjects) {
            auto xPos{entry.second.position_.x};
            auto yPos{entry.second.position_.y};

            if (yPos * tileUnitsWidth + xPos >=
                tileUnitsWidth * tileUnitsWidth / 2) {
                break;
            }

            auto objectType = entry.second.object_->type_;

            auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

            float imageWidth;
            float imageHeight;

            auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};
            if (isSmallObject) {
                imageWidth = imageSize.width / 60.0f * smallObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    CONVERT8WIDTH8TO8HEIGHT(
                        smallObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            } else {
                imageWidth = imageSize.width / 60.0f * largeObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    CONVERT8WIDTH8TO8HEIGHT(
                        largeObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            }

            auto tileWidth{viewWidth - 2 * kMargin.x -
                           static_cast<float>(tileUnitsWidth - yPos) /
                               tileUnitsWidth * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + kMargin.x +
                          static_cast<float>(tileUnitsWidth - yPos) /
                              tileUnitsWidth * viewWidth * 0.3f};

            auto baseX{tileLeft +
                       static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
            auto baseY{0.75f + kMargin.y +
                       static_cast<float>(yPos + 1) / tileUnitsWidth *
                           (0.25f - 2 * kMargin.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

            auto x{(mousePosition.x - imageX) / imageWidth};
            auto y{(mousePosition.y - imageY) / imageHeight};

            auto isHovered{_<IMAGE8BANK>().IS8PIXEL8VISIBLE(objectType, x, y)};

            if (isHovered) {
                hoveredObject_ = entry.second.object_;

                hoveredCreature_ = nullptr;

                hoveredThingMouseOffset_ = {mousePosition.x - baseX,
                                            mousePosition.y - baseY};
            }
        }

        auto creature{facedTile->creature_};

        if (creature) {
            auto creatureType{creature->type_};

            auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(creatureType)};

            auto imageWidth{imageSize.width / 60.0f * largeObjectScale};
            auto imageHeight{imageSize.height / 60.0f *
                             CONVERT8WIDTH8TO8HEIGHT(largeObjectScale)};

            auto tileWidth{viewWidth - 2 * kMargin.x - 0.5f * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + kMargin.x +
                          0.5f * viewWidth * 0.3f};

            auto baseX{tileLeft + 0.5f * tileWidth};
            auto baseY{0.75f + kMargin.y + 0.5f * (0.25f - 2 * kMargin.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            auto scale{largeObjectScale};

            auto x{(mousePosition.x - imageX) / imageWidth};
            auto y{(mousePosition.y - imageY) / imageHeight};

            auto isHovered{
                _<IMAGE8BANK>().IS8PIXEL8VISIBLE(creatureType, x, y)};

            if (isHovered) {
                hoveredObject_ = nullptr;

                hoveredCreature_ = creature;

                hoveredThingMouseOffset_ = {mousePosition.x - baseX,
                                            mousePosition.y - baseY};
            }
        }

        for (auto entry : orderedObjects) {
            auto xPos{entry.second.position_.x};
            auto yPos{entry.second.position_.y};

            if (yPos * tileUnitsWidth + xPos <
                tileUnitsWidth * tileUnitsWidth / 2) {
                continue;
            }

            auto objectType = entry.second.object_->type_;

            auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

            float imageWidth;
            float imageHeight;

            auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};

            if (isSmallObject) {
                imageWidth = imageSize.width / 60.0f * smallObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    CONVERT8WIDTH8TO8HEIGHT(
                        smallObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            } else {
                imageWidth = imageSize.width / 60.0f * largeObjectScale *
                             (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                             tileUnitsWidth;
                imageHeight =
                    imageSize.height / 60.0f *
                    CONVERT8WIDTH8TO8HEIGHT(
                        largeObjectScale *
                        (tileUnitsWidth - (tileUnitsWidth - yPos) / 2) /
                        tileUnitsWidth);
            }

            auto tileWidth{viewWidth - 2 * kMargin.x -
                           static_cast<float>(tileUnitsWidth - yPos) /
                               tileUnitsWidth * viewWidth * 0.6f};
            auto tileLeft{1.0f - viewWidth + kMargin.x +
                          static_cast<float>(tileUnitsWidth - yPos) /
                              tileUnitsWidth * viewWidth * 0.3f};

            auto baseX{tileLeft +
                       static_cast<float>(xPos) / tileUnitsWidth * tileWidth};
            auto baseY{0.75f + kMargin.y +
                       static_cast<float>(yPos + 1) / tileUnitsWidth *
                           (0.25f - 2 * kMargin.y)};

            auto imageX{baseX - imageWidth / 2.0f};
            auto imageY{baseY - imageHeight};

            auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

            auto x{(mousePosition.x - imageX) / imageWidth};
            auto y{(mousePosition.y - imageY) / imageHeight};

            auto isHovered{_<IMAGE8BANK>().IS8PIXEL8VISIBLE(objectType, x, y)};

            if (isHovered) {
                hoveredObject_ = entry.second.object_;

                hoveredCreature_ = nullptr;

                hoveredThingMouseOffset_ = {mousePosition.x - baseX,
                                            mousePosition.y - baseY};
            }
        }
    }

    void
    FIRST8PERSON8HOVERING::RENDER() {
        auto mousePosition{GET8MOUSE8POSITION()};

        if (hoveredObject_) {
            auto objectLabel{
                _<OBJECT8INDEX>().GET8OBJECT8LABEL(hoveredObject_->type_)};

            if (objectLabel.empty()) {
                objectLabel = "?";
            }

            _<TEXT8RENDERER>().DRAW8STRING(objectLabel, mousePosition.x,
                                           mousePosition.y + kTextYOffset_);
        } else if (hoveredCreature_) {
            auto creatureLabel{_<CREATURE8INDEX>().GET8CREATURE8LABEL(
                hoveredCreature_->type_)};

            if (creatureLabel.empty()) {
                creatureLabel = "?";
            }

            _<TEXT8RENDERER>().DRAW8STRING(creatureLabel, mousePosition.x,
                                           mousePosition.y + kTextYOffset_);
        }
    }
}