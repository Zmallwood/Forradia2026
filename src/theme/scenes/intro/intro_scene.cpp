#include "intro_scene.hpp"
#include "core/rendering/image_renderer.hpp"
#include "core/scenes_core/scene_manager.hpp"

namespace darktale
{
    void intro_scene::render_derived()
    {
        _<image_renderer>().draw_image("default_scene_background", 0.0f, 0.0f,
                                       1.0f, 1.0f);

        _<image_renderer>().draw_image("darktale_logo", 0.2f, 0.2f, 0.6f, 0.2f);
    }

    void intro_scene::on_key_down(SDL_Keycode key)
    {
        _<scene_manager>().go_to_scene("main_menu_scene");
    }

    void intro_scene::on_mouse_down(Uint8 button)
    {
        _<scene_manager>().go_to_scene("main_menu_scene");
    }
}