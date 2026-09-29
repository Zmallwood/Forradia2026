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

    class PlayerInventory
    {
      public:
        void AddObject(std::string_view objectName);

        std::shared_ptr<Object> GetObject(int index);

        std::shared_ptr<Object> PickObject(int index);

      private:
        static constexpr int k_maxObjects_{1000};
        std::unordered_map<int, std::shared_ptr<Object>> objects_;
    };
}