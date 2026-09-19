/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#pragma once

#include "image_entry.hpp"

namespace Forradia
{
    class image_bank
    {
      public:
        void load_images();

        std::shared_ptr<SDL_Texture> get_image(int imageNameHash);

        size get_image_size(int imageNameHash);

      private:
        void load_single_image(std::string_view full_path);

        static constexpr std::string_view k_relative_images_directory_{
            "resources/Images/"};
        std::unordered_map<int, image_entry> images_;
    };
}