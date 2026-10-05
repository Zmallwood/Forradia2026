// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUIPanel.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

GUIPanel::GUIPanel(float x, float y, float width, float height)
    : GUIComponent(x, y), size_(width, height)
{
}

void GUIPanel::RenderDerived()
{
    auto position{GetPosition()};

    _<ImageRenderer>().DrawImage(GetBackgroundImage(), position.x, position.y,
                                 size_.width, size_.height);
}

std::string GUIPanel::GetBackgroundImage()
{
    return k_defaultBackgroundImage_;
}

RectF GUIPanel::GetBounds()
{
    auto position{GetPosition()};

    return {position.x, position.y, size_.width, size_.height};
}