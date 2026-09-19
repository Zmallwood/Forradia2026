#pragma once

#include "core/scenes_core/i_scene.hpp"

namespace darktale
{
    class world_generation_scene : public i_scene
    {
      protected:
        void on_enter() override;
    };
}