#pragma once

namespace darktale
{
    class first_person_view
    {
      public:
        void render();

      private:
        static constexpr float k_view_width_{0.5f};
        static constexpr point_f k_margin_{0.03f, 0.01f};
    };
}