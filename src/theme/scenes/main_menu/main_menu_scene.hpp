#pragma once

#include "core/scenes_core/i_scene.hpp"

namespace darktale
{
    class main_menu_scene : public i_scene
    {
      protected:
        void render_derived() override;

        void on_key_down(SDL_Keycode key) override;

        void on_mouse_down(Uint8 button) override;
    };
}