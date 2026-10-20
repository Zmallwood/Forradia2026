// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "WORLD_GENERATION_SCENE.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/SCENES8CORE/SCENE_MANAGER.HPP"
#include "SUB/WORLD_GENERATOR.HPP"

void WorldGenerationScene::OnEnterDerived()
{
    _<WorldGenerator>().GenerateNewWorld();

    _<PLAYER>().SPAWN8ONSUITABLE8LOCATION();

    _<WorldGenerator>().GenerateCivilization();

    _<WorldGenerator>().GenerateWorldAroundPlayer();

    _<SceneManager>().GoToScene("MainScene");
}