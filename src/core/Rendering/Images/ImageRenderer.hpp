// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "Mask.hpp"

class ImageRenderer
{
  public:
    // ImageRenderer();

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

  //   void DrawImageToBuffer(int imageNameHash, float x, float y, float width,
  //                          float height, float opacity = 1.0f,
  //                          bool flipHorizontal = false);

  //   void ApplyMasksToBuffer(std::vector<Mask> &masks);

  //   Mask CreateDiamondMask(float xF, float yF, float widthF, float heightF);

  //   Mask CreateMaskFromImage(std::string_view imageName, float xF, float yF,
  //                            float widthF, float heightF);

  //   void DrawBufferToScreen();

  // private:
  //   std::shared_ptr<SDL_Texture> buffer_;
  //   std::shared_ptr<SDL_Texture> maskBuffer_;
  //   Mask diamondMask_;
  //   SDL_BlendMode alphaMaskBlend_;
  //   SDL_BlendMode unionMaskBlend_;
};