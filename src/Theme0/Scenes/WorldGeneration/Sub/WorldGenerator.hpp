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

    void Traverse1(std::function<void(int, int)> callback);

    void Traverse2(std::function<void(int, int)> callback);

    void Traverse3(std::function<void(int, int)> callback);

    void Traverse4(std::function<void(int, int)> callback);

    void GenerateDirt();

    void GenerateWater();

    void GenerateElevation();

    void GenerateRock();

    void GenerateLargeObjects();

    void GenerateSmallObjects();

    void GenerateCreatures();
};