#include "mouse_utilities.hpp"

namespace Forradia
{
    point_f get_mouse_position()
    {
        auto canvas_size{get_canvas_size()};

        int x, y;

        SDL_GetMouseState(&x, &y);

        return point_f{static_cast<float>(x) / canvas_size.width,
                       static_cast<float>(y) / canvas_size.height};
    }
}