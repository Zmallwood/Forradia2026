#include "tile.hpp"
#include "tile_objects.hpp"

namespace darktale
{
    tile::tile()
    {
        tile_objects_ = std::make_shared<tile_objects>();
    }
}