/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    Size GetCanvasSize();

    float GetAspectRatio();

    float ConvertWidthToHeight(float width);

    float ConvertHeightToWidth(float height);
}