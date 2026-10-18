// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

class Mask
{
  public:
    std::shared_ptr<SDL_Texture> texture_;
    float x_ = 0.0f;
    float y_ = 0.0f;
    float width_ = 0.0f;
    float height_ = 0.0f;
};