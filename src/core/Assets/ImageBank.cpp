/************************************************************************
 *                               Forradia                               *
 *                                                                      *
 * Copyright (c) 2026 Andreas Åkerberg                                  *
 * SPDX-License-Identifier: MIT                                         *
 ************************************************************************/

#include "ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    void ImageBank::LoadImages()
    {
        auto imagesDirectory{SDL_GetBasePath() +
                             std::string(k_relativeImagesDirectory_)};

        imagesDirectory = Replace(imagesDirectory, "\\", "/");

        auto rdi{
            std::filesystem::recursive_directory_iterator(imagesDirectory)};

        for (const auto &entry : rdi)
        {
            if (entry.is_regular_file() && entry.path().extension() == ".png")
            {
                LoadSingleImage(entry.path().string());
            }
        }
    }

    void ImageBank::LoadSingleImage(std::string_view fullPath)
    {
        std::string path{Replace(fullPath, "\\", "/")};

        auto pureName{GetFileNameNoExt(path)};

        auto hash{Hash(pureName)};

        auto loaded{IMG_Load(path.c_str())};

        if (!loaded)
        {
            std::cout << "Failed to load image " << path << ": "
                      << IMG_GetError() << std::endl;
            return;
        }

        auto converted{SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32,
                                                0)};

        SDL_FreeSurface(loaded);

        if (!converted)
        {
            std::cout << "Failed to convert image " << path << ": "
                      << SDL_GetError() << std::endl;
            return;
        }

        auto surface{std::shared_ptr<SDL_Surface>(converted, SDLDeleter())};

        auto texture{std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(_<SDLDevice>().renderer_.get(),
                                         surface.get()),
            SDLDeleter())};

        ImageEntry entry{texture, surface};

        images_.insert({hash, entry});
    }

    std::shared_ptr<SDL_Texture> ImageBank::GetImage(int imageNameHash)
    {
        if (images_.contains(imageNameHash))
        {
            return images_.at(imageNameHash).texture;
        }

        return nullptr;
    }

    Size ImageBank::GetImageSize(int imageNameHash)
    {
        auto width{0};
        auto height{0};

        if (images_.contains(imageNameHash))
        {
            SDL_QueryTexture(images_.at(imageNameHash).texture.get(), nullptr,
                             nullptr, &width, &height);
        }

        return {width, height};
    }

    bool ImageBank::IsPixelVisible(int imageNameHash, float x, float y)
    {
        if (images_.contains(imageNameHash))
        {
            auto surface{images_.at(imageNameHash).surface.get()};

            if (!surface || !surface->pixels || surface->w <= 0 ||
                surface->h <= 0 || x < 0.0f || y < 0.0f || x >= 1.0f ||
                y >= 1.0f)
            {
                return false;
            }

            auto xPx{static_cast<int>(x * static_cast<float>(surface->w))};
            auto yPx{static_cast<int>(y * static_cast<float>(surface->h))};

            if (xPx < 0)
            {
                xPx = 0;
            }

            if (yPx < 0)
            {
                yPx = 0;
            }

            if (xPx >= surface->w)
            {
                xPx = surface->w - 1;
            }

            if (yPx >= surface->h)
            {
                yPx = surface->h - 1;
            }

            auto pixels{static_cast<Uint8 *>(surface->pixels)};
            auto alpha{pixels[yPx * surface->pitch + xPx * 4 + 3]};

            return alpha > 0;
        }

        return false;
    }
}