#pragma once

namespace Forradia
{
    class object;

    class tile_objects
    {
      public:
        void clear();

        void add_object(std::string_view object_name,
                        point position = {-1, -1});

        int count();

        std::map<point, std::shared_ptr<object>> objects_;
    };
}