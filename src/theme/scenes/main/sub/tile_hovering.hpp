#pragma once

namespace darktale
{
    class tile_hovering
    {
      public:
        void update();

        point hovered_coordinate_{-1, -1};
    };
}