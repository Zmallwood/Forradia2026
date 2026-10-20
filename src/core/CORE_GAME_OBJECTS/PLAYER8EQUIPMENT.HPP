// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#pragma once

class OBJECT;

class PLAYER8EQUIPMENT
{
  public:
    std::shared_ptr<OBJECT> headObject_;
    std::shared_ptr<OBJECT> chestObject_;
    std::shared_ptr<OBJECT> legsObject_;
    std::shared_ptr<OBJECT> feetObject_;
    std::shared_ptr<OBJECT> rightHandObject_;
    std::shared_ptr<OBJECT> leftHandObject_;
};