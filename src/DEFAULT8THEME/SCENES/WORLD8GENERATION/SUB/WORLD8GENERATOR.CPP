//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "WORLD8GENERATOR.HPP"
#include "SUB/STARTING8AREA8GENERATOR.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"

namespace FORRADIA8GAME {
    void
    WORLD8GENERATOR::GENERATE8NEW8WORLD() {
        auto cityWorldArea{_<STARTING8AREA8GENERATOR>().GENERATE8WORLD8AREA()};

        _<WORLD>().currentWorldArea_ = cityWorldArea;
    }
}