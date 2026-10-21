//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8EQUIPMENT8WINDOW.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8EQUIPMENT.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/SUB/OBJECT8MOVING.HPP"

namespace FORRADIA8GAME {
    GUI8EQUIPMENT8WINDOW::GUI8EQUIPMENT8WINDOW()
        : GUI8WINDOW("Equipment", 0.45f, 0.3f, 0.2f, 0.4f) {
    }

    bool
    GUI8EQUIPMENT8WINDOW::ON8MOUSE8DOWN(Uint8 mouseButton) {
        auto result{GUI8WINDOW::ON8MOUSE8DOWN(mouseButton)};

        auto mousePosition{GET8MOUSE8POSITION()};

        if (GET8HEAD8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->headObject_);

            _<PLAYER>().playerEquipment_->headObject_ = nullptr;

            return true;
        } else if (GET8CHEST8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->chestObject_);

            _<PLAYER>().playerEquipment_->chestObject_ = nullptr;

            return true;
        } else if (GET8LEGS8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->legsObject_);

            _<PLAYER>().playerEquipment_->legsObject_ = nullptr;

            return true;
        } else if (GET8FEET8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->feetObject_);

            _<PLAYER>().playerEquipment_->feetObject_ = nullptr;

            return true;
        } else if (GET8RIGHT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->rightHandObject_);

            _<PLAYER>().playerEquipment_->rightHandObject_ = nullptr;

            return true;
        } else if (GET8LEFT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->leftHandObject_);

            _<PLAYER>().playerEquipment_->leftHandObject_ = nullptr;

            return true;
        }

        return result;
    }

    bool
    GUI8EQUIPMENT8WINDOW::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) {
        GUI8WINDOW::ON8MOUSE8UP(mouseButton, clickSpeed);

        auto mousePosition{GET8MOUSE8POSITION()};

        if (GET8HEAD8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<PLAYER>().playerEquipment_->headObject_ =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8CHEST8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<PLAYER>().playerEquipment_->chestObject_ =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8LEGS8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<PLAYER>().playerEquipment_->legsObject_ =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8FEET8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<PLAYER>().playerEquipment_->feetObject_ =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8RIGHT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<PLAYER>().playerEquipment_->rightHandObject_ =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8LEFT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<PLAYER>().playerEquipment_->leftHandObject_ =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        }

        return false;
    }

    void
    GUI8EQUIPMENT8WINDOW::RENDER8DERIVED() {
        GUI8WINDOW::RENDER8DERIVED();

        auto headBounds{GET8HEAD8SLOT8BOUNDS()};
        auto chestBounds{GET8CHEST8SLOT8BOUNDS()};
        auto legsBounds{GET8LEGS8SLOT8BOUNDS()};
        auto feetBounds{GET8FEET8SLOT8BOUNDS()};
        auto rightHandBounds{GET8RIGHT8HAND8SLOT8BOUNDS()};
        auto leftHandBounds{GET8LEFT8HAND8SLOT8BOUNDS()};

        _<IMAGE8RENDERER>().DRAW8IMAGE(kHeadSlotImage_, headBounds);
        _<IMAGE8RENDERER>().DRAW8IMAGE(kChestSlotImage_, chestBounds);
        _<IMAGE8RENDERER>().DRAW8IMAGE(kLegsSlotImage_, legsBounds);
        _<IMAGE8RENDERER>().DRAW8IMAGE(kFeetSlotImage_, feetBounds);
        _<IMAGE8RENDERER>().DRAW8IMAGE(kRightHandSlotImage_, rightHandBounds);
        _<IMAGE8RENDERER>().DRAW8IMAGE(kLeftHandSlotImage_, leftHandBounds);

        if (_<PLAYER>().playerEquipment_->headObject_)
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->headObject_->type_, headBounds);

        if (_<PLAYER>().playerEquipment_->chestObject_)
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->chestObject_->type_, chestBounds);

        if (_<PLAYER>().playerEquipment_->legsObject_)
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->legsObject_->type_, legsBounds);

        if (_<PLAYER>().playerEquipment_->feetObject_)
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->feetObject_->type_, feetBounds);

        if (_<PLAYER>().playerEquipment_->rightHandObject_)
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->rightHandObject_->type_,
                rightHandBounds);

        if (_<PLAYER>().playerEquipment_->leftHandObject_)
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->leftHandObject_->type_,
                leftHandBounds);
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8HEAD8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 1};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8CHEST8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 2};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8LEGS8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 3};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8FEET8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 4};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8RIGHT8HAND8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 4.0f * 1};
        auto yCenter{size_.height / 5.0f * 2};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8LEFT8HAND8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 4.0f * 3};
        auto yCenter{size_.height / 5.0f * 2};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }
}