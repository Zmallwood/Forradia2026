//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "OBJECT8MOVING.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"
#include "CORE/WORLD8STRUCTURE/TILE8OBJECTS.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD8AREA.HPP"
#include "FIRST8PERSON8VIEW/FIRST8PERSON8VIEW8FUNCTIONS.HPP"
#include "FIRST8PERSON8HOVERING.HPP"

namespace FORRADIA8GAME {
    void
    OBJECT8MOVING::ON8MOUSE8DOWN(Uint8 button) {
        if (button != SDL_BUTTON_LEFT) {
            return;
        }

        auto viewWidth{GAME8PROPERTIES::kViewWidth_};

        auto mousePosition{GET8MOUSE8POSITION()};

        if (mousePosition.x < viewWidth) {
            return;
        }

        auto hoveredObject{_<FIRST8PERSON8HOVERING>().hoveredObject_};

        if (!hoveredObject) {
            return;
        }

        if (_<OBJECT8INDEX>().OBJECT8UNMOVABLE(hoveredObject->type_)) {
            return;
        }

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto tile{worldArea->GET8TILE(facedTileCoordinate)};

        objectInAir_ = tile->tileObjects_->PICK8OBJECT(hoveredObject);

        draggingMouseOffset_ =
            _<FIRST8PERSON8HOVERING>().hoveredThingMouseOffset_;

        pickedPosition_ = GET8HOVERED8TILE8POSITION(draggingMouseOffset_);
    }

    void
    OBJECT8MOVING::ON8MOUSE8UP(Uint8 button, int clickSpeed) {
        if (!objectInAir_) {
            return;
        }

        if (button != SDL_BUTTON_LEFT) {
            return;
        }

        auto viewWidth{GAME8PROPERTIES::kViewWidth_};

        auto mousePosition{GET8MOUSE8POSITION()};

        auto hoveredTilePosition{
            GET8HOVERED8TILE8POSITION(draggingMouseOffset_)};

        if (mousePosition.x < viewWidth) {
            hoveredTilePosition = pickedPosition_;
        }

        if (hoveredTilePosition == POINT{-1, -1}) {
            hoveredTilePosition = pickedPosition_;
        }

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto tile{worldArea->GET8TILE(facedTileCoordinate)};

        tile->tileObjects_->ADD8OBJECT(objectInAir_, hoveredTilePosition);

        CLEAR8OBJECT();
    }

    void
    OBJECT8MOVING::RENDER() {
        if (!objectInAir_) {
            return;
        }

        auto mousePosition{GET8MOUSE8POSITION()};

        auto objectType{objectInAir_->type_};

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

        constexpr auto largeObjectScale{GAME8PROPERTIES::kLargeObjectScale_};
        constexpr auto smallObjectScale{GAME8PROPERTIES::kSmallObjectScale_};

        auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};

        auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

        auto imageWidth{imageSize.width / 60.0f * scale};
        auto imageHeight{imageSize.height / 60.0f *
                         CONVERT8WIDTH8TO8HEIGHT(scale)};

        auto imageX{mousePosition.x - draggingMouseOffset_.x -
                    imageWidth / 2.0f};
        auto imageY{mousePosition.y - draggingMouseOffset_.y - imageHeight};

        _<IMAGE8RENDERER>().DRAW8IMAGE(objectType, imageX, imageY, imageWidth,
                                       imageHeight);
    }

    void
    OBJECT8MOVING::CLEAR8OBJECT() {
        objectInAir_ = nullptr;

        draggingMouseOffset_ = {0.0f, 0.0f};
    }
}