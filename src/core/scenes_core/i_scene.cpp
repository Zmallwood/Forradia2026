#include "i_scene.hpp"

namespace darktale
{
    void i_scene::update()
    {
        update_derived();
    }

    void i_scene::render()
    {
        render_derived();
    }
}