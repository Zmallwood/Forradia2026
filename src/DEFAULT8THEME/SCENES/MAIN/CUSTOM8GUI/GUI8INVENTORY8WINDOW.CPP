//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI8INVENTORY8WINDOW.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER8INVENTORY.HPP"
#include "CORE/GUI8CORE/WINDOWS/GUI8WINDOW8TITLE8BAR.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/RENDERING/TEXT/TEXT8RENDERER.HPP"
#include "CORE/RENDERING/COLORS/COLOR8RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/SUB/OBJECT8MOVING.HPP"

namespace FORRADIA8GAME {
    GUI8INVENTORY8WINDOW::GUI8INVENTORY8WINDOW()
        : GUI8WINDOW("Inventory", 0.2F, 0.3F, 0.2F, 0.4F) {
    }

    bool
    GUI8INVENTORY8WINDOW::ON8MOUSE8DOWN(Uint8 mouseButton) {
        auto result{GUI8WINDOW::ON8MOUSE8DOWN(mouseButton)};

        auto mousePosition{GET8MOUSE8POSITION()};

        auto bounds{GET8BOUNDS()};

        if (mouseButton == SDL_BUTTON_LEFT && bounds.CONTAINS(mousePosition) &&
            isVisible_ && isEnabled_) {
            auto position{GET8POSITION()};

            auto size{size_};

            auto titleBarHeight{titleBar_->size_.height};

            auto numCols{
                static_cast<int>(size.width / (kSlotWidth_ + kSlotMarginX_))};

            auto slotHeight{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

            auto slotMarginY{CONVERT8WIDTH8TO8HEIGHT(kSlotMarginX_)};

            auto numRows{static_cast<int>((size.height - titleBarHeight) /
                                          (slotHeight + slotMarginY))};

            auto inventoryIndex{0};

            for (auto y = 0; y < numRows; y++) {
                for (auto x = 0; x < numCols; x++) {
                    auto slotX{position.x + kSlotMarginX_ +
                               x * (kSlotWidth_ + kSlotMarginX_)};

                    auto slotY{position.y + titleBarHeight +
                               y * (slotHeight + slotMarginY)};

                    auto slotWidth{kSlotWidth_};

                    RECT8F slotBounds{slotX, slotY, slotWidth, slotHeight};

                    if (slotBounds.CONTAINS(mousePosition)) {
                        auto object{_<PLAYER>().playerInventory_->PICK8OBJECT(
                            inventoryIndex)};

                        if (object) {
                            _<OBJECT8MOVING>().pickedInventoryPosition_ =
                                inventoryIndex;
                            _<OBJECT8MOVING>().SET8OBJECT8IN8AIR(object);

                            constexpr auto largeObjectScale{
                                GAME8PROPERTIES::kLargeObjectScale_};
                            constexpr auto smallObjectScale{
                                GAME8PROPERTIES::kSmallObjectScale_};

                            auto isSmallObject{
                                _<OBJECT8INDEX>().IS8SMALL8OBJECT(
                                    object->type_)};

                            auto scale{isSmallObject ? smallObjectScale
                                                     : largeObjectScale};

                            auto offsetX{(mousePosition.x -
                                          (slotBounds.x + slotWidth / 2.0F)) *
                                         scale / kSlotWidth_};
                            auto offsetY{(mousePosition.y -
                                          (slotBounds.y + slotHeight)) *
                                         scale / kSlotWidth_};

                            _<OBJECT8MOVING>().draggingMouseOffset_ = {offsetX,
                                                                       offsetY};
                        }
                    }

                    ++inventoryIndex;
                }
            }

            return true;
        }

        return result;
    }

    bool
    GUI8INVENTORY8WINDOW::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed) {
        GUI8WINDOW::ON8MOUSE8UP(mouseButton, clickSpeed);

        if (!_<OBJECT8MOVING>().GET8OBJECT8IN8AIR())
            return false;

        auto mousePosition{GET8MOUSE8POSITION()};

        auto position{GET8POSITION()};

        auto size{size_};

        auto titleBarHeight{titleBar_->size_.height};

        auto numCols{
            static_cast<int>(size.width / (kSlotWidth_ + kSlotMarginX_))};

        auto slotHeight{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto slotMarginY{CONVERT8WIDTH8TO8HEIGHT(kSlotMarginX_)};

        auto numRows{static_cast<int>((size.height - titleBarHeight) /
                                      (slotHeight + slotMarginY))};

        auto inventoryIndex{0};

        for (auto y = 0; y < numRows; y++) {
            for (auto x = 0; x < numCols; x++) {
                auto slotX{position.x + kSlotMarginX_ +
                           x * (kSlotWidth_ + kSlotMarginX_)};

                auto slotY{position.y + titleBarHeight +
                           y * (slotHeight + slotMarginY)};

                auto slotWidth{kSlotWidth_};

                RECT8F slotBounds{slotX, slotY, slotWidth, slotHeight};

                if (slotBounds.CONTAINS(mousePosition)) {
                    auto objectOnLocation{
                        _<PLAYER>().playerInventory_->PICK8OBJECT(
                            inventoryIndex)};

                    if (objectOnLocation) {
                        _<OBJECT8MOVING>().MOVE8OBJECT8TO8PICKUP8LOCATION(
                            objectOnLocation);
                    }

                    _<PLAYER>().playerInventory_->ADD8OBJECT(
                        _<OBJECT8MOVING>().GET8OBJECT8IN8AIR(), inventoryIndex);

                    _<OBJECT8MOVING>().CLEAR8OBJECT();

                    return true;
                }

                ++inventoryIndex;
            }
        }

        return false;
    }

    void
    GUI8INVENTORY8WINDOW::RENDER8DERIVED() {
        GUI8WINDOW::RENDER8DERIVED();

        auto mousePosition{GET8MOUSE8POSITION()};

        auto position{GET8POSITION()};

        auto textYOffset{_<GAME8PROPERTIES>().kHoveringLabelYOffset_};

        auto size{size_};

        auto titleBarHeight{titleBar_->size_.height};

        auto numCols{
            static_cast<int>(size.width / (kSlotWidth_ + kSlotMarginX_))};

        auto slotHeight{CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_)};

        auto slotMarginY{CONVERT8WIDTH8TO8HEIGHT(kSlotMarginX_)};

        auto numRows{static_cast<int>((size.height - titleBarHeight) /
                                      (slotHeight + slotMarginY))};

        auto inventoryIndex{0};

        std::string hoveredObjectLabel;

        for (auto y = 0; y < numRows; y++) {
            for (auto x = 0; x < numCols; x++) {
                auto slotX{position.x + kSlotMarginX_ +
                           x * (kSlotWidth_ + kSlotMarginX_)};

                auto slotY{position.y + titleBarHeight +
                           y * (slotHeight + slotMarginY)};

                auto slotWidth{kSlotWidth_};

                _<IMAGE8RENDERER>().DRAW8IMAGE(
                    "GUIInventoryWindowSlotBackground", slotX, slotY, slotWidth,
                    slotHeight);

                auto object{
                    _<PLAYER>().playerInventory_->GET8OBJECT(inventoryIndex)};

                if (object) {
                    _<IMAGE8RENDERER>().DRAW8IMAGE(object->type_, slotX, slotY,
                                                   slotWidth, slotHeight);

                    RECT8F objectBounds{slotX, slotY, slotWidth, slotHeight};

                    if (objectBounds.CONTAINS(mousePosition)) {
                        auto objectLabel{
                            _<OBJECT8INDEX>().GET8OBJECT8LABEL(object->type_)};

                        hoveredObjectLabel = objectLabel;

                        if (hoveredObjectLabel.empty())
                            hoveredObjectLabel = "?";
                    }
                }

                ++inventoryIndex;
            }
        }

        if (!hoveredObjectLabel.empty()) {
            auto textSize{_<TEXT8RENDERER>().MEASURE8STRING(hoveredObjectLabel,
                                                            FONT8SIZES::_20)};

            _<COLOR8RENDERER>().FILL8RECT(
                mousePosition.x, mousePosition.y + textYOffset, textSize.width,
                textSize.height, COLORS::kDarkBlue);

            _<TEXT8RENDERER>().DRAW8STRING(hoveredObjectLabel, mousePosition.x,
                                           mousePosition.y + textYOffset,
                                           FONT8SIZES::_20);
        }
    }
}