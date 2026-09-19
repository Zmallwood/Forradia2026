#pragma once

namespace darktale
{
    class sdl_deleter
    {
      public:
        void operator()(SDL_Window *window);

        void operator()(SDL_Renderer *renderer);

        void operator()(SDL_Surface *surface);

        void operator()(SDL_Texture *texture);

        void operator()(TTF_Font *font);
    };
}