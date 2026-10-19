// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class ImageEntry
{
  public:
    std::shared_ptr<SDL_Texture> texture;
    std::shared_ptr<SDL_Surface> surface;
};