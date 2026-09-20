/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "IScene.hpp"

namespace Forradia
{
    void IScene::Update()
    {
        UpdateDerived();
    }

    void IScene::Render()
    {
        RenderDerived();
    }
}