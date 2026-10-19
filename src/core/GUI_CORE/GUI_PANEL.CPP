// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_PANEL.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"

GUIPanel::GUIPanel(float x, float y, float width, float height)
    : GUIComponent(x, y), size_(width, height)
{
}

bool GUIPanel::OnMouseDown(Uint8 mouseButton)
{
    auto result = GUIComponent::OnMouseDown(mouseButton);

    if (result)
    {
        return true;
    }

    if (!isVisible_ || !isEnabled_)
    {
        return false;
    }

    return GetBounds().CONTAINS(GetMousePosition());
}

void GUIPanel::RenderDerived()
{
    auto position = GetPosition();

    _<ImageRenderer>().DrawImage(GetBackgroundImage(), position.x, position.y,
                                 size_.width, size_.height);
}

std::string GUIPanel::GetBackgroundImage()
{
    return k_defaultBackgroundImage_;
}

RECT_F GUIPanel::GetBounds()
{
    auto position = GetPosition();

    return {position.x, position.y, size_.width, size_.height};
}