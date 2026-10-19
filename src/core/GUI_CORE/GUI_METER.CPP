// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/RENDERING/COLORS/COLOR_RENDERER.HPP"
#include "GUI_METER.HPP"


GUIMeter::GUIMeter(float x, float y, float width, float height)
    : GUIComponent(x, y), size_(width, height)
{
}

void GUIMeter::RenderDerived()
{
    auto position = GetPosition();

    auto size = size_;

    _<ColorRenderer>().FillRect(position.x, position.y, size.width, size.height,
                                COLORS::k_darkBlue);

    _<ColorRenderer>().FillRect(position.x, position.y,
                                GetMeterProgress() * size.width, size.height,
                                GetFilledColor());

    _<ColorRenderer>().DrawRect(position.x, position.y, size.width, size.height,
                                COLORS::k_black);
}

float GUIMeter::GetMeterProgress()
{
    return 0.0f;
}

COLOR GUIMeter::GetFilledColor()
{
    return COLORS::k_yellowGray;
}