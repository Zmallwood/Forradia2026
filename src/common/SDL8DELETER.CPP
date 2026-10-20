//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "SDL8DELETER.HPP"

void
SDL8DELETER::operator()(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}

void
SDL8DELETER::operator()(SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
}

void
SDL8DELETER::operator()(SDL_Surface *surface)
{
    SDL_FreeSurface(surface);
}

void
SDL8DELETER::operator()(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
}

void
SDL8DELETER::operator()(TTF_Font *font)
{
    TTF_CloseFont(font);
}