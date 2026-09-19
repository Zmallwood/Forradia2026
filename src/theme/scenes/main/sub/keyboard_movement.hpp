#pragma once

namespace darktale
{
    class keyboard_movement
    {
      public:
        void update();

        void on_key_down(SDL_Keycode key);

        void on_key_up(SDL_Keycode key);

      private:
        std::set<SDL_Keycode> pressed_keys_;
    };
}