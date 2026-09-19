#include "number_utilities.hpp"

namespace darktale
{
    int invert_speed(float speed)
    {
        return static_cast<int>(1000 / speed);
    }
}