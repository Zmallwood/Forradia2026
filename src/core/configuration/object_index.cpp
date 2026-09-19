/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "object_index.hpp"
#include "object_flags.hpp"

namespace Forradia
{
    object_index::object_index()
    {
        entries_.insert(
            {get_hash("object_stone"), {object_flags::k_small_object}});

        entries_.insert(
            {get_hash("object_branch"), {object_flags::k_small_object}});

        entries_.insert(
            {get_hash("object_pink_flower"), {object_flags::k_small_object}});

        entries_.insert(
            {get_hash("object_leaf"), {object_flags::k_small_object}});
    }

    bool object_index::is_small_object(int object_hash)
    {
        return entries_[object_hash].flags & object_flags::k_small_object;
    }
}