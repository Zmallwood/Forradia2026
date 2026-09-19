#pragma once

namespace darktale
{
    class sdl_device
    {
      public:
        sdl_device();

        void clear_canvas();

        void present_canvas();

        void clip(float x, float y, float width, float height);

        void reset_clip();

        std::shared_ptr<SDL_Window> window_;
        std::shared_ptr<SDL_Renderer> renderer_;

      private:
        static constexpr std::string_view k_window_name_{"Darktale"};
    };
}