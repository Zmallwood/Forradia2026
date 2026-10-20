// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/RENDERING/COLORS/COLOR_RENDERER.HPP"
#include "GUI8METER.HPP"

GUI8METER::GUI8METER(float x, float y, float width, float height)
    : GUI8COMPONENT(x, y), size_(width, height)
{
}

void GUI8METER::RENDER8DERIVED()
{
    auto position = GET8POSITION();

    auto size = size_;

    _<ColorRenderer>().FillRect(position.x, position.y, size.width, size.height,
                                COLORS::k_darkBlue);

    _<ColorRenderer>().FillRect(position.x, position.y,
                                GET8METER8PROGRESS() * size.width, size.height,
                                GET8FILLED8COLOR());

    _<ColorRenderer>().DrawRect(position.x, position.y, size.width, size.height,
                                COLORS::k_black);
}

float GUI8METER::GET8METER8PROGRESS()
{
    return 0.0f;
}

COLOR GUI8METER::GET8FILLED8COLOR()
{
    return COLORS::k_yellowGray;
}