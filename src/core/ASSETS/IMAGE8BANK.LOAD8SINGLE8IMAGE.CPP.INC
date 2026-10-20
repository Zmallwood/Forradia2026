//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

std::string path = REPLACE(fullPath, "\\", "/");

auto pureName = GET8FILE8NAME8NO8EXT(path);

auto hash = HASH(pureName);

auto loaded = IMG_Load(path.c_str());

if (!loaded)
{
    std::cout << "Failed to load image " << path << ": " << IMG_GetError()
              << std::endl;
    return;
}

auto converted = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32, 0);

SDL_FreeSurface(loaded);

if (!converted)
{
    std::cout << "Failed to convert image " << path << ": " << SDL_GetError()
              << std::endl;
    return;
}

auto surface = std::shared_ptr<SDL_Surface>(converted, SDL8DELETER());

auto texture = std::shared_ptr<SDL_Texture>(
    SDL_CreateTextureFromSurface(_<SDL8DEVICE>().renderer_.get(),
                                 surface.get()),
    SDL8DELETER());

IMAGE8ENTRY entry{texture, surface};

images_.insert({hash, entry});