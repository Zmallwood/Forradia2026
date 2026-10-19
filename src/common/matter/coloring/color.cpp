// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "COLOR.HPP"

SDL_Color COLOR::TO_SDL_COLOR()
{
    return {static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255),
            static_cast<Uint8>(b * 255), static_cast<Uint8>(a * 255)};
}