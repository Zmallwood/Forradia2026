/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class SDLDeleter
    {
      public:
        void operator()(SDL_Window *window);

        void operator()(SDL_Renderer *renderer);

        void operator()(SDL_Surface *surface);

        void operator()(SDL_Texture *texture);

        void operator()(TTF_Font *font);
    };
}