// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "NPC.HPP"

NPC::NPC(std::string_view typeName) : type_(HASH(typeName))
{
}