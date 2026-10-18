// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "ImageRenderer.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

// ImageRenderer::ImageRenderer()
// {
//     auto canvasSize = GetCanvasSize();

//     buffer_ = std::shared_ptr<SDL_Texture>(
//         SDL_CreateTexture(_<SDLDevice>().renderer_.get(),
//                           SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
//                           canvasSize.width, canvasSize.height),
//         SDLDeleter());

//     maskBuffer_ = std::shared_ptr<SDL_Texture>(
//         SDL_CreateTexture(_<SDLDevice>().renderer_.get(),
//                           SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
//                           canvasSize.width, canvasSize.height),
//         SDLDeleter());

//     if (buffer_)
//     {
//         SDL_SetTextureBlendMode(buffer_.get(), SDL_BLENDMODE_NONE);
//     }

//     if (maskBuffer_)
//     {
//         SDL_SetTextureBlendMode(maskBuffer_.get(), SDL_BLENDMODE_NONE);
//     }

//     alphaMaskBlend_ = SDL_ComposeCustomBlendMode(
//         SDL_BLENDFACTOR_ZERO, // Source RGB factor
//         SDL_BLENDFACTOR_ONE,  // Destination RGB factor
//         SDL_BLENDOPERATION_ADD,

//         SDL_BLENDFACTOR_ZERO,      // Source alpha factor
//         SDL_BLENDFACTOR_SRC_ALPHA, // Destination alpha factor
//         SDL_BLENDOPERATION_ADD);

//     // Binary mask alphas saturate, so overlapping layers form a union.
//     unionMaskBlend_ = SDL_ComposeCustomBlendMode(
//         SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD,
//         SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
// }

void ImageRenderer::DrawImage(int imageNameHash, float x, float y, float width,
                              float height, float opacity, bool flipHorizontal)
{
    auto canvasSize = GetCanvasSize();

    auto xPx = static_cast<int>(x * canvasSize.width);
    auto yPx = static_cast<int>(y * canvasSize.height);
    auto widthPx = static_cast<int>(width * canvasSize.width);
    auto heightPx = static_cast<int>(height * canvasSize.height);

    auto rect = SDL_Rect{xPx, yPx, widthPx, heightPx};

    auto image = _<ImageBank>().GetImage(imageNameHash);

    SDL_RendererFlip flip =
        flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    auto opacityInt = static_cast<int>(opacity * 255);

    SDL_SetTextureAlphaMod(image.get(), opacityInt);

    SDL_RenderCopyEx(_<SDLDevice>().renderer_.get(), image.get(), nullptr,
                     &rect, 0, nullptr, flip);

    SDL_SetTextureAlphaMod(image.get(), 255);
}

void ImageRenderer::DrawImage(std::string_view imageName, float x, float y,
                              float width, float height, float opacity,
                              bool flipHorizontal)
{
    auto hash = Hash(imageName);

    DrawImage(hash, x, y, width, height, opacity, flipHorizontal);
}

void ImageRenderer::DrawImage(int imageNameHash, RectF bounds, float opacity,
                              bool flipHorizontal)
{
    DrawImage(imageNameHash, bounds.x, bounds.y, bounds.width, bounds.height,
              opacity, flipHorizontal);
}

void ImageRenderer::DrawImage(std::string_view imageName, RectF bounds,
                              float opacity, bool flipHorizontal)
{
    DrawImage(imageName, bounds.x, bounds.y, bounds.width, bounds.height,
              opacity, flipHorizontal);
}

// namespace
// {
//     struct ClipState
//     {
//         SDL_bool enabled = SDL_FALSE;
//         SDL_Rect rect{};
//     };

//     ClipState DisableClip(SDL_Renderer *renderer)
//     {
//         ClipState state;
//         state.enabled = SDL_RenderIsClipEnabled(renderer);

//         if (state.enabled == SDL_TRUE)
//         {
//             SDL_RenderGetClipRect(renderer, &state.rect);
//             SDL_RenderSetClipRect(renderer, nullptr);
//         }

//         return state;
//     }

//     void RestoreClip(SDL_Renderer *renderer, const ClipState &state)
//     {
//         if (state.enabled == SDL_TRUE)
//         {
//             SDL_RenderSetClipRect(renderer, &state.rect);
//         }
//     }
// }

// void ImageRenderer::DrawImageToBuffer(int imageNameHash, float x, float y,
//                                       float width, float height, float opacity,
//                                       bool flipHorizontal)
// {
//     if (!buffer_)
//     {
//         return;
//     }

//     auto renderer = _<SDLDevice>().renderer_.get();
//     auto clip = DisableClip(renderer);

//     SDL_SetTextureBlendMode(buffer_.get(), SDL_BLENDMODE_NONE);
//     SDL_SetRenderTarget(renderer, buffer_.get());

//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//     SDL_RenderClear(renderer);

//     DrawImage(imageNameHash, x, y, width, height, opacity, flipHorizontal);

//     SDL_SetRenderTarget(renderer, nullptr);
//     RestoreClip(renderer, clip);
// }

// void ImageRenderer::ApplyMasksToBuffer(std::vector<Mask> &masks)
// {
//     if (!buffer_ || !maskBuffer_ || masks.empty())
//     {
//         return;
//     }

//     auto canvasSize = GetCanvasSize();
//     auto canvasW = canvasSize.width;
//     auto canvasH = canvasSize.height;

//     auto renderer = _<SDLDevice>().renderer_.get();
//     auto clip = DisableClip(renderer);

//     SDL_BlendMode previousDrawBlend = SDL_BLENDMODE_NONE;
//     SDL_GetRenderDrawBlendMode(renderer, &previousDrawBlend);

//     Uint8 previousR = 0;
//     Uint8 previousG = 0;
//     Uint8 previousB = 0;
//     Uint8 previousA = 0;
//     SDL_GetRenderDrawColor(renderer, &previousR, &previousG, &previousB,
//                            &previousA);

//     SDL_SetTextureBlendMode(maskBuffer_.get(), SDL_BLENDMODE_NONE);
//     SDL_SetRenderTarget(renderer, maskBuffer_.get());
//     SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//     SDL_RenderClear(renderer);

//     auto applied = false;

//     for (auto &mask : masks)
//     {
//         if (!mask.texture_)
//         {
//             continue;
//         }

//         auto xPx = static_cast<int>(mask.x_ * canvasW);
//         auto yPx = static_cast<int>(mask.y_ * canvasH);
//         auto widthPx = static_cast<int>(mask.width_ * canvasW);
//         auto heightPx = static_cast<int>(mask.height_ * canvasH);

//         if (widthPx <= 0 || heightPx <= 0)
//         {
//             continue;
//         }

//         auto dest = SDL_Rect{xPx, yPx, widthPx, heightPx};

//         SDL_SetTextureBlendMode(mask.texture_.get(), unionMaskBlend_);
//         SDL_RenderCopy(renderer, mask.texture_.get(), nullptr, &dest);
//         SDL_SetTextureBlendMode(mask.texture_.get(), SDL_BLENDMODE_NONE);

//         applied = true;
//     }

//     if (applied)
//     {
//         SDL_SetTextureBlendMode(buffer_.get(), SDL_BLENDMODE_NONE);
//         SDL_SetRenderTarget(renderer, buffer_.get());

//         SDL_SetTextureBlendMode(maskBuffer_.get(), alphaMaskBlend_);
//         SDL_RenderCopy(renderer, maskBuffer_.get(), nullptr, nullptr);
//         SDL_SetTextureBlendMode(maskBuffer_.get(), SDL_BLENDMODE_NONE);
//     }

//     SDL_SetRenderDrawColor(renderer, previousR, previousG, previousB,
//                            previousA);
//     SDL_SetRenderDrawBlendMode(renderer, previousDrawBlend);

//     SDL_SetRenderTarget(renderer, nullptr);
//     RestoreClip(renderer, clip);
// }

// Mask ImageRenderer::CreateDiamondMask(float xF, float yF, float widthF,
//                                       float heightF)
// {
//     auto canvasSize = GetCanvasSize();

//     auto width = static_cast<int>(widthF * canvasSize.width);
//     auto height = static_cast<int>(heightF * canvasSize.height);

//     if (width <= 0 || height <= 0)
//     {
//         return Mask();
//     }

//     auto placeMask = [&](Mask mask)
//     {
//         mask.x_ = xF;
//         mask.y_ = yF;
//         mask.width_ = widthF;
//         mask.height_ = heightF;
//         return mask;
//     };

//     if (diamondMask_.texture_)
//     {
//         int cachedWidth = 0;
//         int cachedHeight = 0;

//         SDL_QueryTexture(diamondMask_.texture_.get(), nullptr, nullptr,
//                          &cachedWidth, &cachedHeight);

//         if (cachedWidth == width && cachedHeight == height)
//         {
//             return placeMask(diamondMask_);
//         }
//     }

//     std::vector<Uint32> pixels(static_cast<size_t>(width) * height, 0x00000000);

//     for (int py = 0; py < height; ++py)
//     {
//         for (int px = 0; px < width; ++px)
//         {
//             const float dx = static_cast<float>(std::abs(px * 2 + 1 - width)) /
//                              static_cast<float>(width);
//             const float dy = static_cast<float>(std::abs(py * 2 + 1 - height)) /
//                              static_cast<float>(height);

//             const Uint8 alpha = (dx + dy <= 1.0f) ? 255 : 0;

//             pixels[static_cast<size_t>(py) * width + px] =
//                 (static_cast<Uint32>(alpha) << 24) | 0x00FFFFFF;
//         }
//     }

//     auto maskTexture = std::shared_ptr<SDL_Texture>(
//         SDL_CreateTexture(_<SDLDevice>().renderer_.get(),
//                           SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
//                           width, height),
//         SDLDeleter());

//     if (!maskTexture)
//     {
//         return Mask();
//     }

//     Mask mask;
//     mask.texture_ = maskTexture;

//     if (SDL_UpdateTexture(mask.texture_.get(), nullptr, pixels.data(),
//                           width * sizeof(Uint32)) != 0)
//     {
//         return Mask();
//     }

//     SDL_SetTextureBlendMode(mask.texture_.get(), SDL_BLENDMODE_NONE);

//     diamondMask_ = mask;

//     return placeMask(mask);
// }

// // std::shared_ptr<SDL_Texture>
// // ImageRenderer::CreateMaskFromImage(std::string_view imageName, float xF,
// //                                    float yF)
// // {
// // }

// void ImageRenderer::DrawBufferToScreen()
// {
//     if (!buffer_)
//     {
//         return;
//     }

//     auto renderer = _<SDLDevice>().renderer_.get();

//     SDL_SetRenderTarget(renderer, nullptr);
//     SDL_SetTextureBlendMode(buffer_.get(), SDL_BLENDMODE_BLEND);

//     SDL_RenderCopy(renderer, buffer_.get(), nullptr, nullptr);
// }

// Mask ImageRenderer::CreateMaskFromImage(std::string_view imageName, float xF,
//                                         float yF, float widthF, float heightF)
// {
//     auto imageSurface = _<ImageBank>().GetImageSurface(Hash(imageName));

//     if (!imageSurface || widthF <= 0 || heightF <= 0)
//     {
//         return Mask();
//     }

//     auto source = imageSurface.get();

//     if (!source->pixels || source->w <= 0 || source->h <= 0)
//     {
//         return Mask();
//     }

//     auto canvasSize = GetCanvasSize();

//     auto width = static_cast<int>(widthF * canvasSize.width);
//     auto height = static_cast<int>(heightF * canvasSize.height);

//     if (width <= 0 || height <= 0)
//     {
//         return Mask();
//     }

//     SDL_Surface *mask = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
//                                                        SDL_PIXELFORMAT_RGBA32);

//     if (!mask)
//     {
//         return Mask();
//     }

//     // Start with a fully transparent mask.
//     SDL_FillRect(mask, nullptr, SDL_MapRGBA(mask->format, 0, 0, 0, 0));

//     if (SDL_MUSTLOCK(source) && SDL_LockSurface(source) != 0)
//     {
//         SDL_FreeSurface(mask);
//         return Mask();
//     }

//     if (SDL_MUSTLOCK(mask) && SDL_LockSurface(mask) != 0)
//     {
//         if (SDL_MUSTLOCK(source))
//         {
//             SDL_UnlockSurface(source);
//         }

//         SDL_FreeSurface(mask);
//         return Mask();
//     }

//     auto opaque = SDL_MapRGBA(mask->format, 255, 255, 255, 255);
//     auto sourceBytesPerPixel = source->format->BytesPerPixel;
//     auto maskBytesPerPixel = mask->format->BytesPerPixel;

//     for (int dy = 0; dy < height; ++dy)
//     {
//         auto sy = static_cast<int>(static_cast<float>(dy) /
//                                    static_cast<float>(height) *
//                                    static_cast<float>(source->h));

//         if (sy >= source->h)
//         {
//             sy = source->h - 1;
//         }

//         auto *sourceRow =
//             static_cast<Uint8 *>(source->pixels) + sy * source->pitch;
//         auto *maskRow = static_cast<Uint8 *>(mask->pixels) + dy * mask->pitch;

//         for (int dx = 0; dx < width; ++dx)
//         {
//             auto sx = static_cast<int>(static_cast<float>(dx) /
//                                        static_cast<float>(width) *
//                                        static_cast<float>(source->w));

//             if (sx >= source->w)
//             {
//                 sx = source->w - 1;
//             }

//             Uint32 sourcePixel = 0;
//             SDL_memcpy(&sourcePixel, sourceRow + sx * sourceBytesPerPixel,
//                        sourceBytesPerPixel);

//             Uint8 r, g, b, a;
//             SDL_GetRGBA(sourcePixel, source->format, &r, &g, &b, &a);

//             if (a == 0)
//             {
//                 continue;
//             }

//             SDL_memcpy(maskRow + dx * maskBytesPerPixel, &opaque,
//                        maskBytesPerPixel);
//         }
//     }

//     if (SDL_MUSTLOCK(mask))
//     {
//         SDL_UnlockSurface(mask);
//     }

//     if (SDL_MUSTLOCK(source))
//     {
//         SDL_UnlockSurface(source);
//     }

//     auto texture = std::shared_ptr<SDL_Texture>(
//         SDL_CreateTextureFromSurface(_<SDLDevice>().renderer_.get(), mask),
//         SDLDeleter());

//     SDL_FreeSurface(mask);

//     if (!texture)
//     {
//         return Mask();
//     }

//     SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_NONE);

//     Mask result;
//     result.texture_ = texture;
//     result.x_ = xF;
//     result.y_ = yF;
//     result.width_ = widthF;
//     result.height_ = heightF;

//     return result;
// }