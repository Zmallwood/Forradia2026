// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/RENDERING/TEXT/TEXT_RENDERER.HPP"
#include "GUI8WINDOW.HPP"
#include "GUI8WINDOW8TITLE8BAR.HPP"


GUI8WINDOW8TITLE8BAR::GUI8WINDOW8TITLE8BAR(std::string_view title, float width,
                                           GUI8WINDOW &guiWindow)
    : GUIPanel(0.0f, 0.0f, width, 0.05f), title_(title), guiWindow_(guiWindow)
{
}

void GUI8WINDOW8TITLE8BAR::UpdateDerived()
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

bool GUI8WINDOW8TITLE8BAR::OnMouseDown(Uint8 mouseButton)
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

bool GUI8WINDOW8TITLE8BAR::OnMouseUp(Uint8 mouseButton, int clickSpeed)
{
    auto mousePosition = GET8MOUSE8POSITION();

    if (GetBounds().CONTAINS(mousePosition))
    {
        isMoving_ = false;

        return true;
    }

    return false;
}

void GUI8WINDOW8TITLE8BAR::RenderDerived()
{
    GUIPanel::RenderDerived();

    auto position = GetPosition();

    _<TextRenderer>().DrawString(title_, position.x + k_margin_.x,
                                 position.y + k_margin_.y, FontSizes::_18,
                                 false);
}

std::string GUI8WINDOW8TITLE8BAR::GetBackgroundImage()
{
    return k_defaultBackgroundImage_;
}

POINT8F GUI8WINDOW8TITLE8BAR::GetPosition()
{
    return guiWindow_.GetPosition();
}

void GUI8WINDOW8TITLE8BAR::SetPosition(POINT8F value)
{
    guiWindow_.SetPosition(value);
}