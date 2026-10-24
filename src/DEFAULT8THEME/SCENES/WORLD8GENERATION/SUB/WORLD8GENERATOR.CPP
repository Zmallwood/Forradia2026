//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "WORLD8GENERATOR.HPP"
#include "CITY8GENERATOR.HPP"
#include "CORE/WORLD8STRUCTURE/WORLD.HPP"

namespace FORRADIA8GAME {
    void WORLD8GENERATOR::GENERATE8NEW8WORLD() {
        auto cityWorldArea{_<CITY8GENERATOR>().GENERATE8CITY()};

        _<WORLD>().currentWorldArea_ = cityWorldArea;
    }
}