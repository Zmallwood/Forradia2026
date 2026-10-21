//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME {
    class IMAGE8RENDERER {
      public:
        void DRAW8IMAGE(int imageNameHash, float x, float y, float width,
                        float height, float opacity = 1.0F,
                        bool flipHorizontal = false);

        void DRAW8IMAGE(std::string_view imageName, float x, float y,
                        float width, float height, float opacity = 1.0F,
                        bool flipHorizontal = false);

        void DRAW8IMAGE(int imageNameHash, RECT8F bounds, float opacity = 1.0F,
                        bool flipHorizontal = false);

        void DRAW8IMAGE(std::string_view imageName, RECT8F bounds,
                        float opacity = 1.0F, bool flipHorizontal = false);

        void DRAW8IMAGE8AUTOSIZE(std::string_view imageName, float x, float y,
                                 float width, float opacity = 1.0F,
                                 bool flipHorizontal = false);
    };
}