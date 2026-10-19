// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "CURSOR.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"

Cursor::Cursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

void Cursor::Reset()
{
    cursorStyle_ = CursorStyles::Default;
}

void Cursor::Render()
{
    auto mousePosition = GetMousePosition();

    auto cursorWidth = k_cursorSize_;
    auto cursorHeight = CONVERT_WIDTH_TO_HEIGHT(cursorWidth);

    std::string cursorImage;

    switch (cursorStyle_)
    {
    case CursorStyles::Hovering:
        cursorImage = "CursorHovering";
        break;
    case CursorStyles::Default:
    default:
        cursorImage = "CursorDefault";
        break;
    }

    _<ImageRenderer>().DrawImage(cursorImage, mousePosition.x - cursorWidth / 2,
                                 mousePosition.y - cursorHeight / 2,
                                 cursorWidth, cursorHeight);
}