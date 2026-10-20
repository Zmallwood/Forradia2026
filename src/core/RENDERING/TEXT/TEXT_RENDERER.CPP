// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CORE/SDL_DEVICE/SDL_DEVICE.HPP"
#include "TEXT_RENDERER.HPP"

void TextRenderer::Initialize()
{
    TTF_Init();

    AddFont(FontSizes::_12);
    AddFont(FontSizes::_18);
    AddFont(FontSizes::_24);
}

void TextRenderer::AddFont(FontSizes fontSize)
{
    auto absFontPath = std::string(SDL_GetBasePath()) + kDefaultFontPath_;
    auto fontPath = REPLACE(absFontPath, "\\", "/");
    auto fontSizeN = static_cast<int>(fontSize);

    auto newFont = std::shared_ptr<TTF_Font>(
        TTF_OpenFont(fontPath.c_str(), fontSizeN), SDL8DELETER());

    fonts_.insert({fontSize, newFont});
}

void TextRenderer::DrawString(std::string_view text, float x, float y,
                              FontSizes fontSize, bool centered, COLOR color)
{
    if (text.empty())
    {
        return;
    }

    auto font = fonts_[fontSize];

    auto sdlColor = color.TO8SDL8COLOR();

    auto surface = std::shared_ptr<SDL_Surface>(
        TTF_RenderText_Solid(font.get(), text.data(), sdlColor), SDL8DELETER());

    auto texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(_<SDLDevice>().renderer_.get(),
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

    SDL_RenderCopy(_<SDLDevice>().renderer_.get(), texture.get(), nullptr,
                   &rect);
}