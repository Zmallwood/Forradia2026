#pragma once

namespace Forradia
{
    class color
    {
      public:
        SDL_Color to_sdl_color();

        float r{0.0f};
        float g{0.0f};
        float b{0.0f};
        float a{1.0f};
    };
}