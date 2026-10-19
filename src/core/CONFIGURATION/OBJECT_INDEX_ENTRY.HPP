// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Object;

class ObjectIndexEntry
{
  public:
    std::string label;
    int flags = 0;
    std::vector<POINT_F> impactPoints;
    std::vector<int> impactObjects;
    std::function<void()> singleImpactPointCompletedAction;
    std::function<void(std::shared_ptr<Object>)> allImpactPointsCompletedAction;
    int worldViewObjectType = 0;
    POINT_F worldViewRenderOffset = {0.0f, 0.0f};
    POINT_F firstPersonViewRenderOffset = {0.0f, 0.0f};
};