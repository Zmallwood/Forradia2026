/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ImageRenderer.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    void ImageRenderer::DrawImage(int imageNameHash, float x, float y,
                                  float width, float height)
    {
        auto canvasSize{GetCanvasSize()};

        auto xPx{static_cast<int>(x * canvasSize.width)};
        auto yPx{static_cast<int>(y * canvasSize.height)};
        auto widthPx{static_cast<int>(width * canvasSize.width)};
        auto heightPx{static_cast<int>(height * canvasSize.height)};

        auto rect{SDL_Rect{xPx, yPx, widthPx, heightPx}};

        auto image{_<ImageBank>().GetImage(imageNameHash)};

        SDL_RenderCopy(_<SDLDevice>().renderer_.get(), image.get(), nullptr,
                       &rect);
    }

    void ImageRenderer::DrawImage(std::string_view imageName, float x, float y,
                                  float width, float height)
    {
        auto hash{Hash(imageName)};

        DrawImage(hash, x, y, width, height);
    }
}