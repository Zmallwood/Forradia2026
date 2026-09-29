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

      private:
        std::vector<std::shared_ptr<Object>> objects_;
    };
}