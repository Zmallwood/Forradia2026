/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIInventoryWindow.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/CoreGameObjects/PlayerInventory.hpp"
#include "Core/GUICore/Windows/GUIWindowTitleBar.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Theme0/Scenes/Main/Sub/ObjectMoving.hpp"

namespace Forradia
{
    GUIInventoryWindow::GUIInventoryWindow()
        : GUIWindow("Inventory", 0.2f, 0.3f, 0.2f, 0.4f)
    {
    }

    bool GUIInventoryWindow::OnMouseDown(Uint8 mouseButton)
    {
        GUIWindow::OnMouseDown(mouseButton);

        auto mousePosition{GetMousePosition()};

        auto bounds{GetBounds()};

        if (mouseButton == SDL_BUTTON_LEFT && bounds.Contains(mousePosition) &&
            isVisible_ && isEnabled_)
        {
            auto position{GetPosition()};

            auto size{size_};

            auto titleBarHeight{titleBar_->size_.height};

            auto numCols{
                static_cast<int>(size.width / (k_slotWidth_ + k_slotMarginX_))};

            auto slotHeight{ConvertWidthToHeight(k_slotWidth_)};

            auto slotMarginY{ConvertWidthToHeight(k_slotMarginX_)};

            auto numRows{static_cast<int>((size.height - titleBarHeight) /
                                          (slotHeight + slotMarginY))};

            auto inventoryIndex{0};

            for (auto y = 0; y < numRows; y++)
            {
                for (auto x = 0; x < numCols; x++)
                {
                    auto slotX{position.x + k_slotMarginX_ +
                               x * (k_slotWidth_ + k_slotMarginX_)};

                    auto slotY{position.y + titleBarHeight +
                               y * (slotHeight + slotMarginY)};

                    auto slotWidth{k_slotWidth_};

                    auto slotBounds =
                        RectF{slotX, slotY, slotWidth, slotHeight};

                    if (slotBounds.Contains(mousePosition))
                    {
                        auto object{_<Player>().playerInventory_->PickObject(
                            inventoryIndex)};

                        if (object)
                        {
                            _<ObjectMoving>().objectInAir_ = object;
                        }
                    }

                    ++inventoryIndex;
                }
            }

            return true;
        }

        return false;
    }

    void GUIInventoryWindow::RenderDerived()
    {
        GUIPanel::RenderDerived();

        auto position{GetPosition()};

        auto size{size_};

        auto titleBarHeight{titleBar_->size_.height};

        auto numCols{
            static_cast<int>(size.width / (k_slotWidth_ + k_slotMarginX_))};

        auto slotHeight{ConvertWidthToHeight(k_slotWidth_)};

        auto slotMarginY{ConvertWidthToHeight(k_slotMarginX_)};

        auto numRows{static_cast<int>((size.height - titleBarHeight) /
                                      (slotHeight + slotMarginY))};

        auto inventoryIndex{0};

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numCols; x++)
            {
                auto slotX{position.x + k_slotMarginX_ +
                           x * (k_slotWidth_ + k_slotMarginX_)};

                auto slotY{position.y + titleBarHeight +
                           y * (slotHeight + slotMarginY)};

                auto slotWidth{k_slotWidth_};

                _<ImageRenderer>().DrawImage("GUIInventoryWindowSlotBackground",
                                             slotX, slotY, slotWidth,
                                             slotHeight);

                auto object{
                    _<Player>().playerInventory_->GetObject(inventoryIndex)};

                if (object)
                {
                    _<ImageRenderer>().DrawImage(object->type_, slotX, slotY,
                                                 slotWidth, slotHeight);
                }

                ++inventoryIndex;
            }
        }
    }
}