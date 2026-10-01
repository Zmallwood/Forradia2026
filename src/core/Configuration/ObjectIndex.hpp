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

        bool ObjectBlocksSight(int objectHash);

        bool ObjectUnmovable(int objectHash);

        std::vector<PointF> GetImpactPoints(int objectHash);

        std::vector<int> GetImpactObjects(int objectHash);

        int GetImpactCompleteTransformToObject(int objectHash);

      private:
        void AddEntry(std::string_view objectName, std::string_view label,
                      int flags, std::vector<PointF> impactPoints = {},
                      std::vector<std::string> impactObjects = {},
                      std::string impactCompleteTransformToObject = {});

        std::unordered_map<int, ObjectIndexEntry> entries_;
    };
}