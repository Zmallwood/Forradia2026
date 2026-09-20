/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "WorldGenerationScene.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Sub/WorldGenerator.hpp"

namespace Forradia
{
    void WorldGenerationScene::OnEnter()
    {
        _<WorldGenerator>().GenerateNewWorld();

        _<SceneManager>().GoToScene("main_scene");
    }
}