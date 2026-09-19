#include "time_utilities.hpp"

namespace Forradia
{
    int ticks()
    {
        return SDL_GetTicks();
    }
}