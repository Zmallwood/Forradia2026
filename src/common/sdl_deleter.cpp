#include "sdl_deleter.hpp"

namespace darktale
{
    void sdl_deleter::operator()(SDL_Window *window)
    {
        SDL_DestroyWindow(window);
    }

    void sdl_deleter::operator()(SDL_Renderer *renderer)
    {
        SDL_DestroyRenderer(renderer);
    }

    void sdl_deleter::operator()(SDL_Surface *surface)
    {
        SDL_FreeSurface(surface);
    }

    void sdl_deleter::operator()(SDL_Texture *texture)
    {
        SDL_DestroyTexture(texture);
    }

    void sdl_deleter::operator()(TTF_Font *font)
    {
        TTF_CloseFont(font);
    }
}