#include "time_utilities.hpp"

namespace darktale
{
    int ticks()
    {
        return SDL_GetTicks();
    }
}