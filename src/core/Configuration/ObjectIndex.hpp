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

        bool IsSmallObject(int objectHash);

        std::string GetObjectLabel(int objectHash);

      private:
        void AddEntry(std::string_view objectName, std::string_view label,
                      int flags);

        std::unordered_map<int, ObjectIndexEntry> entries_;
    };
}