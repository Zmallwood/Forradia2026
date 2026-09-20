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
    class object_index
    {
      public:
        object_index();

        bool is_small_object(int object_hash);

      private:
        std::unordered_map<int, object_index_entry> entries_;
    };
}