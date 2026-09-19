#include "world.hpp"
#include "core/world_structure/world_area.hpp"

namespace darktale
{
    world::world()
    {
        current_world_area_ = std::make_shared<world_area>();
    }
}