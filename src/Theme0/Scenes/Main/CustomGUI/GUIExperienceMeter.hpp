/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "Core/GUICore/GUIMeter.hpp"

class GUIExperienceMeter : public GUIMeter
{
  public:
    GUIExperienceMeter();

  protected:
    virtual float GetMeterProgress() override;
};