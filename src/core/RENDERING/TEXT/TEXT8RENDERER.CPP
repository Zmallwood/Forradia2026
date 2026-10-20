//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "TEXT8RENDERER.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"

namespace FORRADIA
{
    void
    TEXT8RENDERER::INITIALIZE()
    {
        TTF_Init();

        ADD8FONT(FONT8SIZES::_12);
        ADD8FONT(FONT8SIZES::_18);
        ADD8FONT(FONT8SIZES::_24);
    }

    void
    TEXT8RENDERER::ADD8FONT(FONT8SIZES fontSize)
    {
        auto absFontPath = std::string(SDL_GetBasePath()) + kDefaultFontPath_;
        auto fontPath = REPLACE(absFontPath, "\\", "/");
        auto fontSizeN = static_cast<int>(fontSize);

        auto newFont = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(fontPath.c_str(), fontSizeN), SDL8DELETER());

        fonts_.insert({fontSize, newFont});
    }

    void
    TEXT8RENDERER::DRAW8STRING(std::string_view text, float x, float y,
                               FONT8SIZES fontSize, bool centered, COLOR color)
    {
        if (text.empty())
        {
            return;
        }

        auto font = fonts_[fontSize];

        auto sdlColor = color.TO8SDL8COLOR();

        auto surface = std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Solid(font.get(), text.data(), sdlColor),
            SDL8DELETER());

        auto texture = std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(_<SDL8DEVICE>().renderer_.get(),
                                         surface.get()),
            SDL8DELETER());

        auto canvasSize = GET8CANVAS8SIZE();

        SDL_Rect rect = {static_cast<int>(x * canvasSize.width),
                         static_cast<int>(y * canvasSize.height), surface->w,
                         surface->h};

        if (centered)
        {
            rect.x -= surface->w / 2;
            rect.y -= surface->h / 2;
        }

        SDL_RenderCopy(_<SDL8DEVICE>().renderer_.get(), texture.get(), nullptr,
                       &rect);
    }
}