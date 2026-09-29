/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIWindowTitleBar.hpp"
#include "GUIWindow.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"

namespace Forradia
{
    GUIWindowTitleBar::GUIWindowTitleBar(std::string_view title, float width,
                                         GUIWindow &guiWindow)
        : GUIPanel(0.0f, 0.0f, width, 0.05f), title_(title),
          guiWindow_(guiWindow)
    {
    }

    void GUIWindowTitleBar::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto mousePosition{GetMousePosition()};

        if (isMoving_)
        {
            auto delta{mousePosition - mousePositionStartMove_};

            auto newPosition{positionStartMove_ + delta};

            SetPosition(newPosition);
        }
    }

    bool GUIWindowTitleBar::OnMouseDown(Uint8 mouseButton)
    {
        auto mousePosition{GetMousePosition()};

        if (GetBounds().Contains(mousePosition))
        {
            positionStartMove_ = GetPosition();

            mousePositionStartMove_ = GetMousePosition();

            isMoving_ = true;

            return true;
        }

        return false;
    }

    bool GUIWindowTitleBar::OnMouseUp(Uint8 mouseButton, int clickSpeed)
    {
        auto mousePosition{GetMousePosition()};

        if (GetBounds().Contains(mousePosition))
        {
            isMoving_ = false;

            return true;
        }

        return false;
    }

    void GUIWindowTitleBar::RenderDerived()
    {
        GUIPanel::RenderDerived();

        auto position{GetPosition()};

        _<TextRenderer>().DrawString(title_, position.x + k_margin_.x,
                                     position.y + k_margin_.y, FontSizes::_18,
                                     false);
    }

    std::string GUIWindowTitleBar::GetBackgroundImage()
    {
        return k_defaultBackgroundImage_;
    }

    PointF GUIWindowTitleBar::GetPosition()
    {
        return guiWindow_.GetPosition();
    }

    void GUIWindowTitleBar::SetPosition(PointF value)
    {
        guiWindow_.SetPosition(value);
    }
}