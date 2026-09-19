#include "world_generation_scene.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "sub/world_generator.hpp"

namespace darktale
{
    void world_generation_scene::on_enter()
    {
        _<world_generator>().generate_new_world();

        _<scene_manager>().go_to_scene("main_scene");
    }
}