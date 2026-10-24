//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "IMAGE8BANK.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"

namespace FORRADIA8GAME {
    void
    IMAGE8BANK::LOAD8IMAGES() {
        auto imagesDirectory{SDL_GetBasePath() +
                             std::string(mkRelativeImagesDirectory)};

        imagesDirectory = REPLACE(imagesDirectory, "\\", "/");

        auto rdi{
            std::filesystem::recursive_directory_iterator(imagesDirectory)};

        for (const auto &entry : rdi)
            if (entry.is_regular_file() && entry.path().extension() == ".png")
                LOAD8SINGLE8IMAGE(entry.path().string());
    }

    void
    IMAGE8BANK::LOAD8SINGLE8IMAGE(std::string_view fullPath) {
        std::string path{REPLACE(fullPath, "\\", "/")};

        auto pureName{GET8FILE8NAME8NO8EXT(path)};

        auto hash{HASH(pureName)};

        auto loaded{IMG_Load(path.c_str())};

        if (!loaded) {
            std::cout << "Failed to load image " << path << ": "
                      << IMG_GetError() << std::endl;
            return;
        }

        auto converted{
            SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32, 0)};

        SDL_FreeSurface(loaded);

        if (!converted) {
            std::cout << "Failed to convert image " << path << ": "
                      << SDL_GetError() << std::endl;
            return;
        }

        auto surface{std::shared_ptr<SDL_Surface>(converted, SDL8DELETER())};

        auto texture{std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(_<SDL8DEVICE>().mRenderer.get(),
                                         surface.get()),
            SDL8DELETER())};

        IMAGE8ENTRY entry{texture, surface};

        mImages.insert({hash, entry});
    }

    std::shared_ptr<SDL_Texture>
    IMAGE8BANK::GET8IMAGE(int imageNameHash) {
        if (mImages.contains(imageNameHash))
            return mImages.at(imageNameHash).texture;
        return nullptr;
    }

    SIZE
    IMAGE8BANK::GET8IMAGE8SIZE(int imageNameHash) {
        auto width{0};
        auto height{0};

        if (mImages.contains(imageNameHash))
            SDL_QueryTexture(mImages.at(imageNameHash).texture.get(), nullptr,
                             nullptr, &width, &height);

        return {width, height};
    }

    bool
    IMAGE8BANK::IS8PIXEL8VISIBLE(int imageNameHash, float x, float y) {
        if (mImages.contains(imageNameHash)) {
            auto surface{mImages.at(imageNameHash).surface.get()};

            if (!surface || !surface->pixels || surface->w <= 0 ||
                surface->h <= 0 || x < 0.0F || y < 0.0F || x >= 1.0F ||
                y >= 1.0F)
                return false;

            auto xPx{static_cast<int>(x * static_cast<float>(surface->w))};
            auto yPx{static_cast<int>(y * static_cast<float>(surface->h))};

            if (xPx < 0)
                xPx = 0;

            if (yPx < 0)
                yPx = 0;

            if (xPx >= surface->w)
                xPx = surface->w - 1;

            if (yPx >= surface->h)
                yPx = surface->h - 1;

            auto pixels{static_cast<Uint8 *>(surface->pixels)};
            auto alpha{pixels[yPx * surface->pitch + xPx * 4 + 3]};

            return alpha > 0;
        }

        return false;
    }
}