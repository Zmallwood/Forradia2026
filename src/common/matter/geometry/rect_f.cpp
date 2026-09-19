#include "rect_f.hpp"

namespace darktale
{
    bool rect_f::contains(point_f point)
    {
        return point.x >= x && point.x <= x + width && point.y >= y &&
               point.y <= y + height;
    }
}