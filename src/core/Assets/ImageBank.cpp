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

        auto surface{
            std::shared_ptr<SDL_Surface>(IMG_Load(path.c_str()), SDLDeleter())};

        if (!surface)
        {
            std::cout << "Failed to load image " << path << ": "
                      << IMG_GetError() << std::endl;
            return;
        }

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

    bool ImageBank::IsPixelVisible(int imageNameHash, int x, int y)
    {
        if (images_.contains(imageNameHash))
        {
            auto surface{images_.at(imageNameHash).surface.get()};

            if (!surface || x < 0 || y < 0 || x >= surface->w ||
                y >= surface->h)
            {
                return false;
            }

            if (SDL_MUSTLOCK(surface))
            {
                SDL_LockSurface(surface);
            }

            Uint32 pixel{*reinterpret_cast<Uint32 *>(
                static_cast<Uint8 *>(surface->pixels) + y * surface->pitch +
                x * surface->format->BytesPerPixel)};

            Uint8 alpha;

            SDL_GetRGBA(pixel, surface->format, nullptr, nullptr, nullptr,
                        &alpha);

            if (SDL_MUSTLOCK(surface))
            {
                SDL_UnlockSurface(surface);
            }

            return alpha > 0;
        }

        return false;
    }
}