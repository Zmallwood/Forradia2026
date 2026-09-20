/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "ImageEntry.hpp"

namespace Forradia
{
    class ImageBank
    {
      public:
        void LoadImages();

        std::shared_ptr<SDL_Texture> GetImage(int imageNameHash);

        Size GetImageSize(int imageNameHash);

      private:
        void LoadSingleImage(std::string_view full_path);

        static constexpr std::string_view k_relativeImagesDirectory_{
            "resources/Images/"};
        std::unordered_map<int, ImageEntry> images_;
    };
}