// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_WINDOW_TITLE_BAR.HPP"
#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "GUI_WINDOW.HPP"

GUIWindowTitleBar::GUIWindowTitleBar(std::string_view title, float width,
                                     GUIWindow &guiWindow)
    : GUIPanel(0.0f, 0.0f, width, 0.05f), title_(title), guiWindow_(guiWindow)
{
}

void GUIWindowTitleBar::UpdateDerived()
{
    GUIPanel::UpdateDerived();

    auto mousePosition = GET8MOUSE8POSITION();

    if (isMoving_)
    {
        auto delta = mousePosition - mousePositionStartMove_;

        auto newPosition = positionStartMove_ + delta;

        SetPosition(newPosition);
    }
}

bool GUIWindowTitleBar::OnMouseDown(Uint8 mouseButton)
{
    auto mousePosition = GET8MOUSE8POSITION();

    if (GetBounds().CONTAINS(mousePosition))
    {
        positionStartMove_ = GetPosition();

        mousePositionStartMove_ = GET8MOUSE8POSITION();

        isMoving_ = true;

        return true;
    }

    return false;
}

bool GUIWindowTitleBar::OnMouseUp(Uint8 mouseButton, int clickSpeed)
{
    auto mousePosition = GET8MOUSE8POSITION();

    if (GetBounds().CONTAINS(mousePosition))
    {
        isMoving_ = false;

        return true;
    }

    return false;
}

void GUIWindowTitleBar::RenderDerived()
{
    GUIPanel::RenderDerived();

    auto position = GetPosition();

    _<TextRenderer>().DrawString(title_, position.x + k_margin_.x,
                                 position.y + k_margin_.y, FontSizes::_18,
                                 false);
}

std::string GUIWindowTitleBar::GetBackgroundImage()
{
    return k_defaultBackgroundImage_;
}

POINT8F GUIWindowTitleBar::GetPosition()
{
    return guiWindow_.GetPosition();
}

void GUIWindowTitleBar::SetPosition(POINT8F value)
{
    guiWindow_.SetPosition(value);
}