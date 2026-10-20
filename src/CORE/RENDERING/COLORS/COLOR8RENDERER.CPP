//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "COLOR8RENDERER.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"

namespace FORRADIA8GAME {
    void
    COLOR8RENDERER::FILL8RECT(float x, float y, float width, float height,
                              COLOR color) {
        auto rect = CREATE8SDL8RECT(x, y, width, height);

        auto sdlColor = color.TO8SDL8COLOR();

        SDL_SetRenderDrawColor(_<SDL8DEVICE>().renderer_.get(), sdlColor.r,
                               sdlColor.g, sdlColor.b, sdlColor.a);

        SDL_RenderFillRect(_<SDL8DEVICE>().renderer_.get(), &rect);
    }

    void
    COLOR8RENDERER::FILL8RECT(RECT8F rect, COLOR color) {
        FILL8RECT(rect.x, rect.y, rect.width, rect.height, color);
    }

    void
    COLOR8RENDERER::DRAW8RECT(float x, float y, float width, float height,
                              COLOR color) {
        auto rect = CREATE8SDL8RECT(x, y, width, height);

        auto sdlColor = color.TO8SDL8COLOR();

        SDL_SetRenderDrawColor(_<SDL8DEVICE>().renderer_.get(), sdlColor.r,
                               sdlColor.g, sdlColor.b, sdlColor.a);

        SDL_RenderDrawRect(_<SDL8DEVICE>().renderer_.get(), &rect);
    }

    void
    COLOR8RENDERER::DRAW8LINE(float x1, float y1, float x2, float y2,
                              COLOR color) {
        auto canvasSize = GET8CANVAS8SIZE();

        auto destX1 = static_cast<int>(x1 * canvasSize.width);
        auto destY1 = static_cast<int>(y1 * canvasSize.height);
        auto destX2 = static_cast<int>(x2 * canvasSize.width);
        auto destY2 = static_cast<int>(y2 * canvasSize.height);

        auto sdlColor = color.TO8SDL8COLOR();

        SDL_SetRenderDrawColor(_<SDL8DEVICE>().renderer_.get(), sdlColor.r,
                               sdlColor.g, sdlColor.b, sdlColor.a);

        SDL_RenderDrawLine(_<SDL8DEVICE>().renderer_.get(), destX1, destY1,
                           destX2, destY2);
    }

    SDL_Rect
    COLOR8RENDERER::CREATE8SDL8RECT(float x, float y, float width,
                                    float height) {
        auto canvasSize = GET8CANVAS8SIZE();

        auto destX = static_cast<int>(std::floor(x * canvasSize.width));
        auto destY = static_cast<int>(std::floor(y * canvasSize.height));
        auto destWidth = static_cast<int>(std::ceil(width * canvasSize.width));
        auto destHeight =
            static_cast<int>(std::ceil(height * canvasSize.height));

        return SDL_Rect{destX, destY, destWidth, destHeight};
    }
}