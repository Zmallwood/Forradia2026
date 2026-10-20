//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "CANVAS8UTILITIES.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"

namespace FORRADIA8GAME {
    SIZE
    GET8CANVAS8SIZE() {
        int width = 0;
        int height = 0;

        SDL_GetWindowSize(_<SDL8DEVICE>().window_.get(), &width, &height);

        return {width, height};
    }

    float
    GET8ASPECT8RATIO() {
        auto size = GET8CANVAS8SIZE();

        return static_cast<float>(size.width) / size.height;
    }

    float
    CONVERT8WIDTH8TO8HEIGHT(float width) {
        return width * GET8ASPECT8RATIO();
    }

    float
    CONVERT8HEIGHT8TO8WIDTH(float height) {
        return height / GET8ASPECT8RATIO();
    }
}