//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "IMAGE8ENTRY.HPP"

namespace FORRADIA8GAME {
    class IMAGE8BANK {
      public:
        void LOAD8IMAGES();

        std::shared_ptr<SDL_Texture> GET8IMAGE(int imageNameHash);

        SIZE GET8IMAGE8SIZE(int imageNameHash);

        bool IS8PIXEL8VISIBLE(int imageNameHash, float x, float y);

      private:
        void LOAD8SINGLE8IMAGE(std::string_view fullPath);

        static constexpr std::string_view kRelativeImagesDirectory{
            "resources/Images/"};
        std::unordered_map<int, IMAGE8ENTRY> mImages;
    };
}