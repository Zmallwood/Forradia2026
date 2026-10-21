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
#include "CORE/CORE8GAME8OBJECTS/PLAYER8EQUIPMENT8SLOTS.HPP"

namespace FORRADIA8GAME {
    GUI8EQUIPMENT8WINDOW::GUI8EQUIPMENT8WINDOW()
        : GUI8WINDOW("Equipment", 0.45F, 0.3F, 0.2F, 0.4F) {
    }

    bool
    GUI8EQUIPMENT8WINDOW::ON8MOUSE8DOWN(Uint8 mouseButton) {
        auto result{GUI8WINDOW::ON8MOUSE8DOWN(mouseButton)};

        auto mousePosition{GET8MOUSE8POSITION()};

        using namespace PLAYER8EQUIPMENT8SLOTS;

        if (GET8HEAD8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->slots_[HEAD]);

            _<OBJECT8MOVING>().pickedEquipmentSlot_ = HEAD;

            _<PLAYER>().playerEquipment_->slots_[HEAD] = nullptr;

            return true;
        } else if (GET8CHEST8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->slots_[CHEST]);

            _<OBJECT8MOVING>().pickedEquipmentSlot_ = CHEST;

            _<PLAYER>().playerEquipment_->slots_[CHEST] = nullptr;

            return true;
        } else if (GET8LEGS8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->slots_[LEGS]);

            _<OBJECT8MOVING>().pickedEquipmentSlot_ = LEGS;

            _<PLAYER>().playerEquipment_->slots_[LEGS] = nullptr;

            return true;
        } else if (GET8FEET8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->slots_[FEET]);

            _<OBJECT8MOVING>().pickedEquipmentSlot_ = FEET;

            _<PLAYER>().playerEquipment_->slots_[FEET] = nullptr;

            return true;
        } else if (GET8RIGHT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->slots_[RIGHT8HAND]);

            _<OBJECT8MOVING>().pickedEquipmentSlot_ = RIGHT8HAND;

            _<PLAYER>().playerEquipment_->slots_[RIGHT8HAND] = nullptr;

            return true;
        } else if (GET8LEFT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(
                _<PLAYER>().playerEquipment_->slots_[LEFT8HAND]);

            _<OBJECT8MOVING>().pickedEquipmentSlot_ = LEFT8HAND;

            _<PLAYER>().playerEquipment_->slots_[LEFT8HAND] = nullptr;

            return true;
        }

        return result;
    }

    bool
    GUI8EQUIPMENT8WINDOW::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) {
        GUI8WINDOW::ON8MOUSE8UP(mouseButton, clickSpeed);

        using namespace PLAYER8EQUIPMENT8SLOTS;

        auto mousePosition{GET8MOUSE8POSITION()};

        if (GET8HEAD8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            if (_<PLAYER>().playerEquipment_->slots_[HEAD]) {
                _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                    _<PLAYER>().playerEquipment_->slots_[HEAD]);
            }

            _<PLAYER>().playerEquipment_->slots_[HEAD] =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8CHEST8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            if (_<PLAYER>().playerEquipment_->slots_[CHEST]) {
                _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                    _<PLAYER>().playerEquipment_->slots_[CHEST]);
            }

            _<PLAYER>().playerEquipment_->slots_[CHEST] =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8LEGS8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            if (_<PLAYER>().playerEquipment_->slots_[LEGS]) {
                _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                    _<PLAYER>().playerEquipment_->slots_[LEGS]);
            }

            _<PLAYER>().playerEquipment_->slots_[LEGS] =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8FEET8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            if (_<PLAYER>().playerEquipment_->slots_[FEET]) {
                _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                    _<PLAYER>().playerEquipment_->slots_[FEET]);
            }

            _<PLAYER>().playerEquipment_->slots_[FEET] =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8RIGHT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            if (_<PLAYER>().playerEquipment_->slots_[RIGHT8HAND]) {
                _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                    _<PLAYER>().playerEquipment_->slots_[RIGHT8HAND]);
            }

            _<PLAYER>().playerEquipment_->slots_[RIGHT8HAND] =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        } else if (GET8LEFT8HAND8SLOT8BOUNDS().CONTAINS(mousePosition)) {
            if (_<PLAYER>().playerEquipment_->slots_[LEFT8HAND]) {
                _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                    _<PLAYER>().playerEquipment_->slots_[LEFT8HAND]);
            }

            _<PLAYER>().playerEquipment_->slots_[LEFT8HAND] =
                _<OBJECT8MOVING>().GET8OBJECT8IN8AIR();

            _<OBJECT8MOVING>().CLEAR8OBJECT();
        }

        return false;
    }

    void
    GUI8EQUIPMENT8WINDOW::RENDER8DERIVED() {
        GUI8WINDOW::RENDER8DERIVED();

        using namespace PLAYER8EQUIPMENT8SLOTS;

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

        if (_<PLAYER>().playerEquipment_->slots_[HEAD])
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->slots_[HEAD]->type_, headBounds);

        if (_<PLAYER>().playerEquipment_->slots_[CHEST])
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->slots_[CHEST]->type_,
                chestBounds);

        if (_<PLAYER>().playerEquipment_->slots_[LEGS])
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->slots_[LEGS]->type_, legsBounds);

        if (_<PLAYER>().playerEquipment_->slots_[FEET])
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->slots_[FEET]->type_, feetBounds);

        if (_<PLAYER>().playerEquipment_->slots_[RIGHT8HAND])
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->slots_[RIGHT8HAND]->type_,
                rightHandBounds);

        if (_<PLAYER>().playerEquipment_->slots_[LEFT8HAND])
            _<IMAGE8RENDERER>().DRAW8IMAGE(
                _<PLAYER>().playerEquipment_->slots_[LEFT8HAND]->type_,
                leftHandBounds);
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8HEAD8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0F};
        auto yCenter{size_.height / 5.0F * 1};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0F};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0F};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8CHEST8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0F};
        auto yCenter{size_.height / 5.0F * 2};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0F};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0F};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8LEGS8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0F};
        auto yCenter{size_.height / 5.0F * 3};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0F};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0F};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8FEET8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 2.0F};
        auto yCenter{size_.height / 5.0F * 4};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0F};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0F};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8RIGHT8HAND8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 4.0F * 1};
        auto yCenter{size_.height / 5.0F * 2};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0F};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0F};

        return {x, y, width, height};
    }

    RECT8F
    GUI8EQUIPMENT8WINDOW::GET8LEFT8HAND8SLOT8BOUNDS() {
        auto position{GET8POSITION()};

        auto xCenter{size_.width / 4.0F * 3};
        auto yCenter{size_.height / 5.0F * 2};

        auto width{kSlotWidth_};
        auto height{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto x{position.x + xCenter - width / 2.0F};
        auto y{position.y + kMarginY_ + yCenter - height / 2.0F};

        return {x, y, width, height};
    }
}