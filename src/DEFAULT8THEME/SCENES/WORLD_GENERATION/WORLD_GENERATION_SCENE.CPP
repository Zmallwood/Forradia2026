//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/SCENES8CORE/SCENE8MANAGER.HPP"
#include "SUB/WORLD_GENERATOR.HPP"
#include "WORLD_GENERATION_SCENE.HPP"

void
WorldGenerationScene::ON8ENTER8DERIVED()
{
    _<WorldGenerator>().GenerateNewWorld();

    _<PLAYER>().SPAWN8ONSUITABLE8LOCATION();

    _<WorldGenerator>().GenerateCivilization();

    _<WorldGenerator>().GenerateWorldAroundPlayer();

    _<SCENE8MANAGER>().GO8TO8SCENE("MainScene");
}