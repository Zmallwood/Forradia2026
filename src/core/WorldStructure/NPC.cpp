/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "NPC.hpp"

namespace Forradia
{
    NPC::NPC(std::string_view typeName) : type_(Hash(typeName))
    {
    }
}