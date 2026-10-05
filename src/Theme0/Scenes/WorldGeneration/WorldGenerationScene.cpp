// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "WorldGenerationScene.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Sub/WorldGenerator.hpp"

void WorldGenerationScene::OnEnterDerived()
{
    _<WorldGenerator>().GenerateNewWorld();

    _<Player>().SpawnOnSuitableLocation();

    _<WorldGenerator>().GenerateCivilization();

    _<SceneManager>().GoToScene("MainScene");
}