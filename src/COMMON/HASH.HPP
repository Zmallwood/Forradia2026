//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    constexpr int
    HASH(std::string_view text) {
        // Use djb2 algorithm by Daniel J. Bernstein.
        unsigned long hash{5381};

        for (char chr : text) {
            constexpr unsigned long algorithmFactor{33};
            hash = algorithmFactor * hash + static_cast<unsigned char>(chr);
        }

        return static_cast<int>(hash);
    }
}