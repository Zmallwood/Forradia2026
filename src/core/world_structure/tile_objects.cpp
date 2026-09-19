#include "tile_objects.hpp"
#include "core/configuration/game_properties.hpp"
#include "object.hpp"

namespace Forradia
{
    void tile_objects::clear()
    {
        objects_.clear();
    }

    void tile_objects::add_object(std::string_view object_name, point position)
    {
        if (position.x == -1 || position.y == -1)
        {
            position.x = rand() % _<game_properties>().k_tile_units_width_;
            position.y = rand() % _<game_properties>().k_tile_units_width_;
        }

        objects_.insert(
            {position, std::make_shared<object>(get_hash(object_name))});
    }

    int tile_objects::count()
    {
        return objects_.size();
    }
}