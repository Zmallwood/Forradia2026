// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"
#include "GUI8PANEL.HPP"

GUI8PANEL::GUI8PANEL(float x, float y, float width, float height)
    : GUI8COMPONENT(x, y), size_(width, height)
{
}

bool GUI8PANEL::ON8MOUSE8DOWN(Uint8 mouseButton)
{
    auto result = GUI8COMPONENT::ON8MOUSE8DOWN(mouseButton);

    if (result)
    {
        return true;
    }

    if (!isVisible_ || !isEnabled_)
    {
        return false;
    }

    return GET8BOUNDS().CONTAINS(GET8MOUSE8POSITION());
}

void GUI8PANEL::RENDER8DERIVED()
{
    auto position = GET8POSITION();

    _<ImageRenderer>().DrawImage(GET8BACKGROUND8IMAGE(), position.x, position.y,
                                 size_.width, size_.height);
}

std::string GUI8PANEL::GET8BACKGROUND8IMAGE()
{
    return k_defaultBackgroundImage_;
}

RECT8F GUI8PANEL::GET8BOUNDS()
{
    auto position = GET8POSITION();

    return {position.x, position.y, size_.width, size_.height};
}