// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Object;

class ObjectIndexEntry
{
  public:
    std::string label;
    int flags = 0;
    std::vector<PointF> impactPoints;
    std::vector<int> impactObjects;
    std::function<void()> singleImpactPointCompletedAction;
    std::function<void(std::shared_ptr<Object>)> allImpactPointsCompletedAction;
    int worldViewObjectType = 0;
};