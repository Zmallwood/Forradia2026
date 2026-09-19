/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "world_generation_scene.hpp"
#include "Core/ScenesCore/scene_manager.hpp"
#include "Sub/world_generator.hpp"

namespace Forradia
{
    void world_generation_scene::on_enter()
    {
        _<world_generator>().generate_new_world();

        _<scene_manager>().go_to_scene("main_scene");
    }
}