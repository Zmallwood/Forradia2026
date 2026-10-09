std::string path = Replace(fullPath, "\\", "/");

auto pureName = GetFileNameNoExt(path);

auto hash = Hash(pureName);

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

auto surface = std::shared_ptr<SDL_Surface>(converted, SDLDeleter());

auto texture = std::shared_ptr<SDL_Texture>(
    SDL_CreateTextureFromSurface(_<SDLDevice>().renderer_.get(), surface.get()),
    SDLDeleter());

ImageEntry entry{texture, surface};

images_.insert({hash, entry});