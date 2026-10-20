//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "GUI_INVENTORY_WINDOW.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT8INDEX.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER8INVENTORY.HPP"
#include "CORE/GUI8CORE/WINDOWS/GUI8WINDOW8TITLE8BAR.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE8RENDERER.HPP"
#include "CORE/WORLD8STRUCTURE/OBJECT.HPP"
#include "DEFAULT8THEME/SCENES/MAIN/SUB/OBJECT_MOVING.HPP"

GUIInventoryWindow::GUIInventoryWindow()
    : GUI8WINDOW("Inventory", 0.2f, 0.3f, 0.2f, 0.4f)
{
}

bool
GUIInventoryWindow::ON8MOUSE8DOWN(Uint8 mouseButton)
{
    auto result = GUI8WINDOW::ON8MOUSE8DOWN(mouseButton);

    auto mousePosition = GET8MOUSE8POSITION();

    auto bounds = GET8BOUNDS();

    if (mouseButton == SDL_BUTTON_LEFT && bounds.CONTAINS(mousePosition) &&
        isVisible_ && isEnabled_)
    {
        auto position = GET8POSITION();

        auto size = size_;

        auto titleBarHeight = titleBar_->size_.height;

        auto numCols =
            static_cast<int>(size.width / (kSlotWidth_ + kSlotMarginX_));

        auto slotHeight = CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_);

        auto slotMarginY = CONVERT8WIDTH8TO8HEIGHT(kSlotMarginX_);

        auto numRows = static_cast<int>((size.height - titleBarHeight) /
                                        (slotHeight + slotMarginY));

        auto inventoryIndex = 0;

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numCols; x++)
            {
                auto slotX = position.x + kSlotMarginX_ +
                             x * (kSlotWidth_ + kSlotMarginX_);

                auto slotY = position.y + titleBarHeight +
                             y * (slotHeight + slotMarginY);

                auto slotWidth = kSlotWidth_;

                RECT8F slotBounds = {slotX, slotY, slotWidth, slotHeight};

                if (slotBounds.CONTAINS(mousePosition))
                {
                    auto object = _<PLAYER>().playerInventory_->PICK8OBJECT(
                        inventoryIndex);

                    if (object)
                    {
                        _<ObjectMoving>().SetObjectInAir(object);

                        constexpr auto largeObjectScale =
                            GAME8PROPERTIES::kLargeObjectScale_;
                        constexpr auto smallObjectScale =
                            GAME8PROPERTIES::kSmallObjectScale_;

                        auto isSmallObject =
                            _<OBJECT8INDEX>().IS8SMALL8OBJECT(object->type_);

                        auto scale =
                            isSmallObject ? smallObjectScale : largeObjectScale;

                        auto offsetX = (mousePosition.x -
                                        (slotBounds.x + slotWidth / 2.0f)) *
                                       scale / kSlotWidth_;
                        auto offsetY =
                            (mousePosition.y - (slotBounds.y + slotHeight)) *
                            scale / kSlotWidth_;

                        _<ObjectMoving>().draggingMouseOffset_ = {offsetX,
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
GUIInventoryWindow::ON8MOUSE8UP(Uint8 mouseButton, int clickSpeed)
{
    GUI8WINDOW::ON8MOUSE8UP(mouseButton, clickSpeed);

    if (!_<ObjectMoving>().GetObjectInAir())
    {
        return false;
    }

    auto mousePosition = GET8MOUSE8POSITION();

    auto position = GET8POSITION();

    auto size = size_;

    auto titleBarHeight = titleBar_->size_.height;

    auto numCols = static_cast<int>(size.width / (kSlotWidth_ + kSlotMarginX_));

    auto slotHeight = CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_);

    auto slotMarginY = CONVERT8WIDTH8TO8HEIGHT(kSlotMarginX_);

    auto numRows = static_cast<int>((size.height - titleBarHeight) /
                                    (slotHeight + slotMarginY));

    auto inventoryIndex = 0;

    for (auto y = 0; y < numRows; y++)
    {
        for (auto x = 0; x < numCols; x++)
        {
            auto slotX =
                position.x + kSlotMarginX_ + x * (kSlotWidth_ + kSlotMarginX_);

            auto slotY =
                position.y + titleBarHeight + y * (slotHeight + slotMarginY);

            auto slotWidth = kSlotWidth_;

            RECT8F slotBounds = {slotX, slotY, slotWidth, slotHeight};

            if (slotBounds.CONTAINS(mousePosition))
            {
                if (!_<PLAYER>().playerInventory_->HAS8OBJECT(inventoryIndex))
                {
                    _<PLAYER>().playerInventory_->ADD8OBJECT(
                        _<ObjectMoving>().GetObjectInAir(), inventoryIndex);

                    _<ObjectMoving>().ClearObject();

                    return true;
                }
            }

            ++inventoryIndex;
        }
    }

    return false;
}

void
GUIInventoryWindow::RENDER8DERIVED()
{
    GUI8WINDOW::RENDER8DERIVED();

    auto position = GET8POSITION();

    auto size = size_;

    auto titleBarHeight = titleBar_->size_.height;

    auto numCols = static_cast<int>(size.width / (kSlotWidth_ + kSlotMarginX_));

    auto slotHeight = CONVERT8WIDTH8TO8HEIGHT(kSlotWidth_);

    auto slotMarginY = CONVERT8WIDTH8TO8HEIGHT(kSlotMarginX_);

    auto numRows = static_cast<int>((size.height - titleBarHeight) /
                                    (slotHeight + slotMarginY));

    auto inventoryIndex = 0;

    for (auto y = 0; y < numRows; y++)
    {
        for (auto x = 0; x < numCols; x++)
        {
            auto slotX =
                position.x + kSlotMarginX_ + x * (kSlotWidth_ + kSlotMarginX_);

            auto slotY =
                position.y + titleBarHeight + y * (slotHeight + slotMarginY);

            auto slotWidth = kSlotWidth_;

            _<IMAGE8RENDERER>().DRAW8IMAGE("GUIInventoryWindowSlotBackground",
                                           slotX, slotY, slotWidth, slotHeight);

            auto object =
                _<PLAYER>().playerInventory_->GET8OBJECT(inventoryIndex);

            if (object)
            {
                _<IMAGE8RENDERER>().DRAW8IMAGE(object->type_, slotX, slotY,
                                               slotWidth, slotHeight);
            }

            ++inventoryIndex;
        }
    }
}