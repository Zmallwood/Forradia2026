//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "WORLD8GENERATION8SCENE.HPP"
#include "CORE/CORE8GAME8OBJECTS/PLAYER.HPP"
#include "CORE/SCENES8CORE/SCENE8MANAGER.HPP"
#include "SUB/WORLD8GENERATOR.HPP"
//#include "SUB/CITY8GENERATOR.HPP"

namespace FORRADIA8GAME {
    void
    WORLD8GENERATION8SCENE::ON8ENTER8DERIVED() {
        _<WORLD8GENERATOR>().GENERATE8NEW8WORLD();
        //_<CITY8GENERATOR>().GENERATE8CITY();
        _<PLAYER>().SPAWN8ONSUITABLE8LOCATION();
        _<SCENE8MANAGER>().GO8TO8SCENE("MainScene");
    }
}