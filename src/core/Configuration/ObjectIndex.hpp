/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "ObjectIndexEntry.hpp"

namespace Forradia
{
    class ObjectIndex
    {
      public:
        ObjectIndex();

        bool IsSmallObject(int object_hash);

      private:
        std::unordered_map<int, ObjectIndexEntry> entries_;
    };
}