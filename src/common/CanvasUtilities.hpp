/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    size get_canvas_size();

    float get_aspect_ratio();

    float convert_width_to_height(float width);

    float convert_height_to_width(float height);
}