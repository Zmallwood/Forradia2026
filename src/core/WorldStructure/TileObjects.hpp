/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Object;

    class TileObjects
    {
      public:
        void Clear();

        void AddObject(std::string_view objectName, Point position = {-1, -1});

        int Count();

        std::map<Point, std::shared_ptr<Object>> objects_;
    };
}