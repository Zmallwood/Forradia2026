// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_INVENTORY_WINDOW.HPP"
#include "CORE/CONFIGURATION/GAME_PROPERTIES.HPP"
#include "CORE/CONFIGURATION/OBJECT_INDEX.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER_INVENTORY.HPP"
#include "CORE/GUI_CORE/WINDOWS/GUI_WINDOW_TITLE_BAR.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"
#include "CORE/WORLD_STRUCTURE/OBJECT.HPP"
#include "THEME_0/SCENES/MAIN/SUB/OBJECT_MOVING.HPP"

GUIInventoryWindow::GUIInventoryWindow()
    : GUIWindow("Inventory", 0.2f, 0.3f, 0.2f, 0.4f)
{
}

bool GUIInventoryWindow::OnMouseDown(Uint8 mouseButton)
{
    auto result = GUIWindow::OnMouseDown(mouseButton);

    auto mousePosition = GetMousePosition();

    auto bounds = GetBounds();

    if (mouseButton == SDL_BUTTON_LEFT && bounds.CONTAINS(mousePosition) &&
        isVisible_ && isEnabled_)
    {
        auto position = GetPosition();

        auto size = size_;

        auto titleBarHeight = titleBar_->size_.height;

        auto numCols =
            static_cast<int>(size.width / (k_slotWidth_ + k_slotMarginX_));

        auto slotHeight = CONVERT_WIDTH_TO_HEIGHT(k_slotWidth_);

        auto slotMarginY = CONVERT_WIDTH_TO_HEIGHT(k_slotMarginX_);

        auto numRows = static_cast<int>((size.height - titleBarHeight) /
                                        (slotHeight + slotMarginY));

        auto inventoryIndex = 0;

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numCols; x++)
            {
                auto slotX = position.x + k_slotMarginX_ +
                             x * (k_slotWidth_ + k_slotMarginX_);

                auto slotY = position.y + titleBarHeight +
                             y * (slotHeight + slotMarginY);

                auto slotWidth = k_slotWidth_;

                RECT_F slotBounds = {slotX, slotY, slotWidth, slotHeight};

                if (slotBounds.CONTAINS(mousePosition))
                {
                    auto object = _<Player>().playerInventory_->PickObject(
                        inventoryIndex);

                    if (object)
                    {
                        _<ObjectMoving>().SetObjectInAir(object);

                        constexpr auto largeObjectScale =
                            GameProperties::k_largeObjectScale_;
                        constexpr auto smallObjectScale =
                            GameProperties::k_smallObjectScale_;

                        auto isSmallObject =
                            _<ObjectIndex>().IsSmallObject(object->type_);

                        auto scale =
                            isSmallObject ? smallObjectScale : largeObjectScale;

                        auto offsetX = (mousePosition.x -
                                        (slotBounds.x + slotWidth / 2.0f)) *
                                       scale / k_slotWidth_;
                        auto offsetY =
                            (mousePosition.y - (slotBounds.y + slotHeight)) *
                            scale / k_slotWidth_;

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

bool GUIInventoryWindow::OnMouseUp(Uint8 mouseButton, int clickSpeed)
{
    GUIWindow::OnMouseUp(mouseButton, clickSpeed);

    if (!_<ObjectMoving>().GetObjectInAir())
    {
        return false;
    }

    auto mousePosition = GetMousePosition();

    auto position = GetPosition();

    auto size = size_;

    auto titleBarHeight = titleBar_->size_.height;

    auto numCols =
        static_cast<int>(size.width / (k_slotWidth_ + k_slotMarginX_));

    auto slotHeight = CONVERT_WIDTH_TO_HEIGHT(k_slotWidth_);

    auto slotMarginY = CONVERT_WIDTH_TO_HEIGHT(k_slotMarginX_);

    auto numRows = static_cast<int>((size.height - titleBarHeight) /
                                    (slotHeight + slotMarginY));

    auto inventoryIndex = 0;

    for (auto y = 0; y < numRows; y++)
    {
        for (auto x = 0; x < numCols; x++)
        {
            auto slotX = position.x + k_slotMarginX_ +
                         x * (k_slotWidth_ + k_slotMarginX_);

            auto slotY =
                position.y + titleBarHeight + y * (slotHeight + slotMarginY);

            auto slotWidth = k_slotWidth_;

            RECT_F slotBounds = {slotX, slotY, slotWidth, slotHeight};

            if (slotBounds.CONTAINS(mousePosition))
            {
                if (!_<Player>().playerInventory_->HasObject(inventoryIndex))
                {
                    _<Player>().playerInventory_->AddObject(
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

void GUIInventoryWindow::RenderDerived()
{
    GUIWindow::RenderDerived();

    auto position = GetPosition();

    auto size = size_;

    auto titleBarHeight = titleBar_->size_.height;

    auto numCols =
        static_cast<int>(size.width / (k_slotWidth_ + k_slotMarginX_));

    auto slotHeight = CONVERT_WIDTH_TO_HEIGHT(k_slotWidth_);

    auto slotMarginY = CONVERT_WIDTH_TO_HEIGHT(k_slotMarginX_);

    auto numRows = static_cast<int>((size.height - titleBarHeight) /
                                    (slotHeight + slotMarginY));

    auto inventoryIndex = 0;

    for (auto y = 0; y < numRows; y++)
    {
        for (auto x = 0; x < numCols; x++)
        {
            auto slotX = position.x + k_slotMarginX_ +
                         x * (k_slotWidth_ + k_slotMarginX_);

            auto slotY =
                position.y + titleBarHeight + y * (slotHeight + slotMarginY);

            auto slotWidth = k_slotWidth_;

            _<ImageRenderer>().DrawImage("GUIInventoryWindowSlotBackground",
                                         slotX, slotY, slotWidth, slotHeight);

            auto object =
                _<Player>().playerInventory_->GetObject(inventoryIndex);

            if (object)
            {
                _<ImageRenderer>().DrawImage(object->type_, slotX, slotY,
                                             slotWidth, slotHeight);
            }

            ++inventoryIndex;
        }
    }
}