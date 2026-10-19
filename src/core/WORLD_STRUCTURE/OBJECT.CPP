// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "OBJECT.HPP"
#include "CORE/CONFIGURATION/OBJECT_INDEX.HPP"

Object::Object(int type) : type_(type)
{
    auto impactPoints = _<ObjectIndex>().GetImpactPoints(type);

    for (auto impactPoint : impactPoints)
    {
        impactPoints_.push_back(CompletableImpactPoint{impactPoint});
    }
}

Object::Object(std::string_view typeName) : Object(Hash(typeName))
{
}