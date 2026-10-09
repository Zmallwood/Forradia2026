// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class ImageRenderer
{
  public:
    void DrawImage(int imageNameHash, float x, float y, float width,
                   float height, float opacity = 1.0f,
                   bool flipHorizontal = false);

    void DrawImage(std::string_view imageName, float x, float y, float width,
                   float height, float opacity = 1.0f,
                   bool flipHorizontal = false);

    void DrawImage(int imageNameHash, RectF bounds, float opacity = 1.0f,
                   bool flipHorizontal = false);

    void DrawImage(std::string_view imageName, RectF bounds,
                   float opacity = 1.0f, bool flipHorizontal = false);
};