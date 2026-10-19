// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "IMAGE_BANK.HPP"
#include "CORE/SDL_DEVICE/SDL_DEVICE.HPP"

void ImageBank::LoadImages()
{
    auto imagesDirectory =
        SDL_GetBasePath() + std::string(k_relativeImagesDirectory_);

    imagesDirectory = Replace(imagesDirectory, "\\", "/");

    auto rdi = std::filesystem::recursive_directory_iterator(imagesDirectory);

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
#include "IMAGE_BANK.LOAD_SINGLE_IMAGE.CPP.INC"
}

std::shared_ptr<SDL_Texture> ImageBank::GetImage(int imageNameHash)
{
    if (images_.contains(imageNameHash))
    {
        return images_.at(imageNameHash).texture;
    }

    return nullptr;
}

SIZE ImageBank::GetImageSize(int imageNameHash)
{
    auto width = 0;
    auto height = 0;

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
        auto surface = images_.at(imageNameHash).surface.get();

        if (!surface || !surface->pixels || surface->w <= 0 ||
            surface->h <= 0 || x < 0.0f || y < 0.0f || x >= 1.0f || y >= 1.0f)
        {
            return false;
        }

        auto xPx = static_cast<int>(x * static_cast<float>(surface->w));
        auto yPx = static_cast<int>(y * static_cast<float>(surface->h));

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

        auto pixels = static_cast<Uint8 *>(surface->pixels);
        auto alpha = pixels[yPx * surface->pitch + xPx * 4 + 3];

        return alpha > 0;
    }

    return false;
}