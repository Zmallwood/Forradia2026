/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "GUIMeter.hpp"
#include "Core/Rendering/Colors/ColorRenderer.hpp"

GUIMeter::GUIMeter(float x, float y, float width, float height)
    : GUIComponent(x, y), size_(width, height)
{
}

void GUIMeter::RenderDerived()
{
    auto position{GetPosition()};

    auto size{size_};

    _<ColorRenderer>().FillRect(position.x, position.y, size.width, size.height,
                                Colors::k_darkBlue);

    _<ColorRenderer>().FillRect(position.x, position.y,
                                GetMeterProgress() * size.width, size.height,
                                GetFilledColor());

    _<ColorRenderer>().DrawRect(position.x, position.y, size.width, size.height,
                                Colors::k_black);
}

float GUIMeter::GetMeterProgress()
{
    return 0.0f;
}

Color GUIMeter::GetFilledColor()
{
    return Colors::k_yellowGray;
}