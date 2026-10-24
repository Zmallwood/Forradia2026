//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "WORLD8AREA.HPP"
#include "CORE/CONFIGURATION/GAME8PROPERTIES.HPP"
#include "CORE/WORLD8STRUCTURE/TILE.HPP"

namespace FORRADIA8GAME {
    WORLD8AREA::WORLD8AREA() {
        auto size{_<GAME8PROPERTIES>().kWorldAreaSize};

        for (auto x = 0; x < size.width; x++) {
            tiles_.push_back(std::vector<std::shared_ptr<TILE>>());

            for (auto y = 0; y < size.height; y++)
                tiles_.at(x).push_back(std::make_shared<TILE>());
        }
    }

    SIZE
    WORLD8AREA::GET8SIZE() {
        auto width{static_cast<int>(tiles_.size())};
        auto height{0};

        if (width)
            height = static_cast<int>(tiles_.at(0).size());

        return {width, height};
    }

    bool
    WORLD8AREA::IS8VALID8COORDINATE(int x, int y) {
        auto size{GET8SIZE()};
        return x >= 0 && x < size.width && y >= 0 && y < size.height;
    }

    bool
    WORLD8AREA::IS8VALID8COORDINATE(POINT coordinate) {
        return IS8VALID8COORDINATE(coordinate.x, coordinate.y);
    }

    std::shared_ptr<TILE>
    WORLD8AREA::GET8TILE(int x, int y) {
        if (IS8VALID8COORDINATE(x, y))
            return tiles_.at(x).at(y);
        return nullptr;
    }

    std::shared_ptr<TILE>
    WORLD8AREA::GET8TILE(POINT coordinate) {
        return GET8TILE(coordinate.x, coordinate.y);
    }
}