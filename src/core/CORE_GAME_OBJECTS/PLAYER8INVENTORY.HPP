// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class Object;

class PLAYER8INVENTORY
{
  public:
    void ADD8OBJECT(std::string_view objectName);

    void ADD8OBJECT(std::shared_ptr<Object> object, int slotIndex);

    std::shared_ptr<Object> GET8OBJECT(int index);

    std::shared_ptr<Object> PICK8OBJECT(int index);

    bool HAS8OBJECT(int index);

  private:
    static constexpr int kMaxObjects_ = 1000;
    std::unordered_map<int, std::shared_ptr<Object>> objects_;
};