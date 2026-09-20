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
    void ImageRenderer::DrawImage(int image_name_hash, float x, float y,
                                  float width, float height)
    {
        auto canvas_size{GetCanvasSize()};

        auto x_px{static_cast<int>(x * canvas_size.width)};
        auto y_px{static_cast<int>(y * canvas_size.height)};
        auto width_px{static_cast<int>(width * canvas_size.width)};
        auto height_px{static_cast<int>(height * canvas_size.height)};

        auto rect{SDL_Rect{x_px, y_px, width_px, height_px}};

        auto image{_<ImageBank>().GetImage(image_name_hash)};

        SDL_RenderCopy(_<SDLDevice>().renderer_.get(), image.get(), nullptr,
                       &rect);
    }

    void ImageRenderer::DrawImage(std::string_view image_name, float x, float y,
                                  float width, float height)
    {
        auto hash{GetHash(image_name)};

        DrawImage(hash, x, y, width, height);
    }
}