/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "IScene.hpp"

namespace Forradia
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