/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIEquipmentWindow.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

namespace Forradia
{
    GUIEquipmentWindow::GUIEquipmentWindow()
        : GUIWindow("Equipment", 0.45f, 0.3f, 0.2f, 0.4f)
    {
    }

    bool GUIEquipmentWindow::OnMouseDown(Uint8 mouseButton)
    {
        GUIWindow::OnMouseDown(mouseButton);

        return false;
    }

    bool GUIEquipmentWindow::OnMouseUp(Uint8 mouseButton, int clickSpeed)
    {
        GUIWindow::OnMouseUp(mouseButton, clickSpeed);

        return false;
    }

    void GUIEquipmentWindow::RenderDerived()
    {
        GUIWindow::RenderDerived();

        _<ImageRenderer>().DrawImage(k_headSlotImage_, GetHeadSlotBounds());
        _<ImageRenderer>().DrawImage(k_chestSlotImage_, GetChestSlotBounds());
        _<ImageRenderer>().DrawImage(k_legsSlotImage_, GetLegsSlotBounds());
        _<ImageRenderer>().DrawImage(k_feetSlotImage_, GetFeetSlotBounds());
        _<ImageRenderer>().DrawImage(k_rightHandSlotImage_,
                                     GetRightHandSlotBounds());
        _<ImageRenderer>().DrawImage(k_leftHandSlotImage_,
                                     GetLeftHandSlotBounds());
    }

    RectF GUIEquipmentWindow::GetHeadSlotBounds()
    {
        auto position{GetPosition()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 1};

        auto width{k_slotWidth_};
        auto height{ConvertWidthToHeight(k_slotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + k_marginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RectF GUIEquipmentWindow::GetChestSlotBounds()
    {
        auto position{GetPosition()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 2};

        auto width{k_slotWidth_};
        auto height{ConvertWidthToHeight(k_slotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + k_marginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RectF GUIEquipmentWindow::GetLegsSlotBounds()
    {
        auto position{GetPosition()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 3};

        auto width{k_slotWidth_};
        auto height{ConvertWidthToHeight(k_slotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + k_marginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RectF GUIEquipmentWindow::GetFeetSlotBounds()
    {
        auto position{GetPosition()};

        auto xCenter{size_.width / 2.0f};
        auto yCenter{size_.height / 5.0f * 4};

        auto width{k_slotWidth_};
        auto height{ConvertWidthToHeight(k_slotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + k_marginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RectF GUIEquipmentWindow::GetRightHandSlotBounds()
    {
        auto position{GetPosition()};

        auto xCenter{size_.width / 4.0f * 1};
        auto yCenter{size_.height / 5.0f * 2};

        auto width{k_slotWidth_};
        auto height{ConvertWidthToHeight(k_slotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + k_marginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }

    RectF GUIEquipmentWindow::GetLeftHandSlotBounds()
    {
        auto position{GetPosition()};

        auto xCenter{size_.width / 4.0f * 3};
        auto yCenter{size_.height / 5.0f * 2};

        auto width{k_slotWidth_};
        auto height{ConvertWidthToHeight(k_slotWidth_)};

        auto x{position.x + xCenter - width / 2.0f};
        auto y{position.y + k_marginY_ + yCenter - height / 2.0f};

        return {x, y, width, height};
    }
}