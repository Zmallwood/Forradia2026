//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "SDL8DELETER.HPP"

namespace FORRADIA8GAME {
    void
    SDL8DELETER::operator()(SDL_Window *window) {
        if (window)
            SDL_DestroyWindow(window);
    }

    void
    SDL8DELETER::operator()(SDL_Renderer *renderer) {
        if (renderer)
            SDL_DestroyRenderer(renderer);
    }

    void
    SDL8DELETER::operator()(SDL_Surface *surface) {
        if (surface)
            SDL_FreeSurface(surface);
    }

    void
    SDL8DELETER::operator()(SDL_Texture *texture) {
        if (texture)
            SDL_DestroyTexture(texture);
    }

    void
    SDL8DELETER::operator()(TTF_Font *font) {
        if (font)
            TTF_CloseFont(font);
    }
}