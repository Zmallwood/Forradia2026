#pragma once

namespace Forradia
{
    class image_renderer
    {
      public:
        void draw_image(int image_name_hash, float x, float y, float width,
                        float height);

        void draw_image(std::string_view image_name, float x, float y,
                        float width, float height);
    };
}
