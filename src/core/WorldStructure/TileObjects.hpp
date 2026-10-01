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

        void AddObject(int objectType, Point position = {-1, -1});

        void AddObject(std::string_view objectName, Point position = {-1, -1});

        void AddObject(std::shared_ptr<Object> object,
                       Point position = {-1, -1});

        int Count();

        void ReplaceObject(std::shared_ptr<Object> object, int objectType);

        std::shared_ptr<Object> PickObject(std::shared_ptr<Object> object);

        std::map<Point, std::shared_ptr<Object>> objects_;
    };
}