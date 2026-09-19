#pragma once

namespace Forradia
{
    class player
    {
      public:
        player();

        void move_north();

        void move_east();

        void move_south();

        void move_west();

        void turn_north();

        void turn_east();

        void turn_south();

        void turn_west();

        point position_{0, 0};
        int ticks_last_movement_{0};
        float movement_speed_{4.0f};
        point destination_{-1, -1};
        point faced_tile_{-1, -1};

      private:
        void spawn_on_suitable_location();
    };
}