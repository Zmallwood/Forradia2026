#pragma once

namespace Forradia
{
    class world_area;

    class world
    {
      public:
        world();

        std::shared_ptr<world_area> current_world_area_;
    };
}