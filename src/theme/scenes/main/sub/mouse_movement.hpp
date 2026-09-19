#pragma once

namespace Forradia
{
    class mouse_movement
    {
      public:
        void update();

        void on_key_down(SDL_Keycode key);

        void on_key_up(SDL_Keycode key);

        void on_mouse_down(Uint8 button);

      private:
        bool ctrl_key_down_{false};
    };
}