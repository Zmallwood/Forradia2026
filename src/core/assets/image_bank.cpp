#include "image_bank.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace Forradia
{
    void image_bank::load_images()
    {
        auto images_directory{SDL_GetBasePath() +
                              std::string(k_relative_images_directory_)};

        images_directory = replace(images_directory, "\\", "/");

        auto rdi{
            std::filesystem::recursive_directory_iterator(images_directory)};

        for (const auto &entry : rdi)
        {
            if (entry.is_regular_file() && entry.path().extension() == ".png")
            {
                load_single_image(entry.path().string());
            }
        }
    }

    void image_bank::load_single_image(std::string_view full_path)
    {
        std::string path{replace(full_path, "\\", "/")};

        auto pure_name{get_file_name_no_ext(path)};

        auto hash{get_hash(pure_name)};

        auto texture{std::shared_ptr<SDL_Texture>(
            IMG_LoadTexture(_<sdl_device>().renderer_.get(), path.c_str()),
            sdl_deleter())};

        if (!texture)
        {
            std::cout << "Failed to load image " << path << ": "
                      << IMG_GetError() << std::endl;
            return;
        }

        images_.insert({hash, texture});
    }

    std::shared_ptr<SDL_Texture> image_bank::get_image(int imageNameHash)
    {
        if (images_.contains(imageNameHash))
        {
            return images_.at(imageNameHash);
        }

        return nullptr;
    }

    size image_bank::get_image_size(int imageNameHash)
    {
        auto width{0};
        auto height{0};

        if (images_.contains(imageNameHash))
        {
            SDL_QueryTexture(images_.at(imageNameHash).get(), nullptr, nullptr,
                             &width, &height);
        }

        return {width, height};
    }
}