#pragma once

namespace darktale
{
    class tile;

    class world_area
    {
      public:
        world_area();

        size get_size();

        bool is_valid_coordinate(int x, int y);

        bool is_valid_coordinate(point coordinate);

        std::shared_ptr<tile> get_tile(int x, int y);

        std::shared_ptr<tile> get_tile(point coordinate);

      private:
        std::vector<std::vector<std::shared_ptr<tile>>> tiles_;
    };
}