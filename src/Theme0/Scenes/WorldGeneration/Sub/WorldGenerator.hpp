// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class WorldGenerator
{
  public:
    void GenerateNewWorld();

    void GenerateCivilization();

  private:
    void ClearWithGrass();

    void GenerateDirt();

    void GenerateWater();

    void GenerateElevation();

    void GenerateRock();

    void GenerateLargeObjects();

    void GenerateSmallObjects();

    void GenerateCreatures();
};