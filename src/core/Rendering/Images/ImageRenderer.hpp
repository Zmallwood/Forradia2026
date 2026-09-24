/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class ImageRenderer
    {
      public:
        void DrawImage(int imageNameHash, float x, float y, float width,
                       float height);

        void DrawImage(std::string_view imageName, float x, float y,
                       float width, float height);
    };
}
