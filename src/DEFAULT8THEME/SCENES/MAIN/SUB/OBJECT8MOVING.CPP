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
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8INVENTORY.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8EQUIPMENT.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8EQUIPMENT8SLOTS.HPP"

namespace FORRADIA8GAME {
    void
    OBJECT8MOVING::ON8MOUSE8DOWN(Uint8 button) {
        if (button != SDL_BUTTON_LEFT)
            return;

        auto viewWidth{GAME8PROPERTIES::kViewWidth_};

        auto mousePosition{GET8MOUSE8POSITION()};

        if (mousePosition.x < viewWidth)
            return;

        auto hoveredObject{_<FIRST8PERSON8HOVERING>().hoveredObject_};

        if (!hoveredObject)
            return;

        if (_<OBJECT8INDEX>().OBJECT8UNMOVABLE(hoveredObject->type_))
            return;

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto tile{worldArea->GET8TILE(facedTileCoordinate)};

        objectInAir_ = tile->tileObjects_->PICK8OBJECT(hoveredObject);

        draggingMouseOffset_ =
            _<FIRST8PERSON8HOVERING>().hoveredThingMouseOffset_;

        SET8PICKED8POSITION(GET8HOVERED8TILE8POSITION(draggingMouseOffset_));
    }

    void
    OBJECT8MOVING::ON8MOUSE8UP(Uint8 button, int clickSpeed) {
        if (!objectInAir_)
            return;

        if (button != SDL_BUTTON_LEFT)
            return;

        auto viewWidth{GAME8PROPERTIES::kViewWidth_};

        auto mousePosition{GET8MOUSE8POSITION()};

        auto hoveredTilePosition{
            GET8HOVERED8TILE8POSITION(draggingMouseOffset_)};

        if (mousePosition.x < viewWidth)
            hoveredTilePosition = pickedPosition_;

        if (hoveredTilePosition == POINT{-1, -1})
            hoveredTilePosition = pickedPosition_;

        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto tile{worldArea->GET8TILE(facedTileCoordinate)};

        auto objectOnLocation{
            tile->tileObjects_->PICK8OBJECT(hoveredTilePosition)};

        if (objectOnLocation)
            MOVE8OBJECT8TO8PICKUP8LOCATION(objectOnLocation);

        tile->tileObjects_->ADD8OBJECT(objectInAir_, hoveredTilePosition);

        CLEAR8OBJECT();
    }

    void
    OBJECT8MOVING::RENDER() {
        if (!objectInAir_)
            return;

        auto mousePosition{GET8MOUSE8POSITION()};

        auto objectType{objectInAir_->type_};

        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(objectType)};

        constexpr auto largeObjectScale{GAME8PROPERTIES::kLargeObjectScale_};
        constexpr auto smallObjectScale{GAME8PROPERTIES::kSmallObjectScale_};

        auto isSmallObject{_<OBJECT8INDEX>().IS8SMALL8OBJECT(objectType)};

        auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

        auto imageWidth{imageSize.width / 60.0F * scale};
        auto imageHeight{imageSize.height / 60.0F *
                         CONVERT8WIDTH8TO8HEIGHT(scale)};

        auto imageX{mousePosition.x - draggingMouseOffset_.x -
                    imageWidth / 2.0F};
        auto imageY{mousePosition.y - draggingMouseOffset_.y - imageHeight};

        _<IMAGE8RENDERER>().DRAW8IMAGE(objectType, imageX, imageY, imageWidth,
                                       imageHeight);
    }

    void
    OBJECT8MOVING::CLEAR8OBJECT() {
        objectInAir_ = nullptr;
        pickedPosition_ = POINT{-1, -1};
        pickedInventoryPosition_ = -1;
        pickedEquipmentSlot_ = -1;
        draggingMouseOffset_ = {0.0F, 0.0F};
    }

    void
    OBJECT8MOVING::MOVE8OBJECT8TO8PICKUP8LOCATION(
        std::shared_ptr<OBJECT> object) {
        if (pickedPosition_ != POINT{-1, -1}) {
            auto worldArea{_<WORLD>().currentWorldArea_};

            auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

            auto tile{worldArea->GET8TILE(facedTileCoordinate)};

            tile->tileObjects_->ADD8OBJECT(object, pickedPosition_);
        } else if (pickedInventoryPosition_ != -1) {
            _<PLAYER>().playerInventory_->ADD8OBJECT(object,
                                                     pickedInventoryPosition_);
        } else if (pickedEquipmentSlot_ != -1) {
            _<PLAYER>().playerEquipment_->slots_[pickedEquipmentSlot_] = object;
        }
    }

    void
    OBJECT8MOVING::SET8PICKED8INVENTORY8POSITION(int position) {
        pickedInventoryPosition_ = position;
        pickedPosition_ = POINT{-1, -1};
        pickedEquipmentSlot_ = -1;
    }

    void
    OBJECT8MOVING::SET8PICKED8EQUIPMENT8SLOT(int slot) {
        pickedEquipmentSlot_ = slot;
        pickedPosition_ = POINT{-1, -1};
        pickedInventoryPosition_ = -1;
    }

    void
    OBJECT8MOVING::SET8PICKED8POSITION(POINT position) {
        pickedPosition_ = position;
        pickedInventoryPosition_ = -1;
        pickedEquipmentSlot_ = -1;
    }
}