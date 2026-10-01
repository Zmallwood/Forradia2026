/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

namespace Forradia
{
    class Object;

    class PlayerEquipment
    {
      public:
        std::shared_ptr<Object> headObject_;
        std::shared_ptr<Object> chestObject_;
        std::shared_ptr<Object> legsObject_;
        std::shared_ptr<Object> feetObject_;
        std::shared_ptr<Object> rightHandObject_;
        std::shared_ptr<Object> leftHandObject_;
    };
}