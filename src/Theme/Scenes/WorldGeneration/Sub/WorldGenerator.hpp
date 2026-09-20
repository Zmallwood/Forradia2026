/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class WorldGenerator
    {
      public:
        void GenerateNewWorld();

      private:
        void ClearWithGrass();

        void GenerateDirt();

        void GenerateWater();

        void GenerateElevation();

        void GenerateRock();

        void GenerateLargeObjects();

        void GenerateSmallObjects();
    };
}