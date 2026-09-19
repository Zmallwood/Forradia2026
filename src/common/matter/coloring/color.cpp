#include "color.hpp"

namespace darktale
{
    SDL_Color color::to_sdl_color()
    {
        return {static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255),
                static_cast<Uint8>(b * 255), static_cast<Uint8>(a * 255)};
    }
}