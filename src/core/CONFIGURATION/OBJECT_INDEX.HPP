// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

#include "OBJECT_INDEX_ENTRY.HPP"

class ObjectIndex
{
  public:
    ObjectIndex();

    bool IsSmallObject(int objectHash);

    std::string GetObjectLabel(int objectHash);

    bool ObjectBlocksSight(int objectHash);

    bool ObjectUnmovable(int objectHash);

    std::vector<POINT_F> GetImpactPoints(int objectHash);

    std::vector<int> GetImpactObjects(int objectHash);

    std::function<void()> GetSingleImpactPointCompletedAction(int objectHash);

    std::function<void(std::shared_ptr<Object>)>
    GetAllImpactPointsCompletedAction(int objectHash);

    int GetWorldViewObjectType(int objectHash);

    POINT_F GetWorldViewRenderOffset(int objectHash);

    POINT_F GetFirstPersonViewRenderOffset(int objectHash);

  private:
    void AddEntry(
        std::string_view objectName, std::string_view label, int flags,
        std::vector<POINT_F> impactPoints = {},
        std::vector<std::string> impactObjects = {},
        std::function<void()> singleImpactPointCompletedAction = []() {},
        std::function<void(std::shared_ptr<Object>)>
            allImpactPointsCompletedAction = [](std::shared_ptr<Object>) {},
        std::string_view worldViewObjectType = "",
        POINT_F worldViewRenderOffset = POINT_F{0.0f, 0.0f},
        POINT_F firstPersonViewRenderOffset = POINT_F{0.0f, 0.0f});

    std::unordered_map<int, ObjectIndexEntry> entries_;
};