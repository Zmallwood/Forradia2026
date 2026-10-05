// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "ImageRenderer.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

void ImageRenderer::DrawImage(int imageNameHash, float x, float y, float width,
                              float height, bool flipHorizontal)
{
    auto canvasSize{GetCanvasSize()};

    auto xPx{static_cast<int>(x * canvasSize.width)};
    auto yPx{static_cast<int>(y * canvasSize.height)};
    auto widthPx{static_cast<int>(width * canvasSize.width)};
    auto heightPx{static_cast<int>(height * canvasSize.height)};

    auto rect{SDL_Rect{xPx, yPx, widthPx, heightPx}};

    auto image{_<ImageBank>().GetImage(imageNameHash)};

    SDL_RendererFlip flip{flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE};

    SDL_RenderCopyEx(_<SDLDevice>().renderer_.get(), image.get(), nullptr,
                     &rect, 0, nullptr, flip);
}

void ImageRenderer::DrawImage(std::string_view imageName, float x, float y,
                              float width, float height, bool flipHorizontal)
{
    auto hash{Hash(imageName)};

    DrawImage(hash, x, y, width, height, flipHorizontal);
}

void ImageRenderer::DrawImage(int imageNameHash, RectF bounds,
                              bool flipHorizontal)
{
    DrawImage(imageNameHash, bounds.x, bounds.y, bounds.width, bounds.height,
              flipHorizontal);
}

void ImageRenderer::DrawImage(std::string_view imageName, RectF bounds,
                              bool flipHorizontal)
{
    DrawImage(imageName, bounds.x, bounds.y, bounds.width, bounds.height,
              flipHorizontal);
}