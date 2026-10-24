//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#include "IMAGE8RENDERER.HPP"
#include "CORE/ASSETS/IMAGE8BANK.HPP"
#include "CORE/SDL8DEVICE/SDL8DEVICE.HPP"

namespace FORRADIA8GAME {
    void
    IMAGE8RENDERER::DRAW8IMAGE(int imageNameHash, float x, float y, float width,
                               float height, float opacity, bool flipHorizontal,
                               SDL_BlendMode blendMode) {
        auto canvasSize{GET8CANVAS8SIZE()};

        auto xPx{static_cast<int>(x * canvasSize.width)};
        auto yPx{static_cast<int>(y * canvasSize.height)};
        auto widthPx{static_cast<int>(width * canvasSize.width)};
        auto heightPx{static_cast<int>(height * canvasSize.height)};

        auto rect{SDL_Rect{xPx, yPx, widthPx, heightPx}};

        auto image{_<IMAGE8BANK>().GET8IMAGE(imageNameHash)};

        SDL_RendererFlip flip{flipHorizontal ? SDL_FLIP_HORIZONTAL
                                             : SDL_FLIP_NONE};

        auto opacityInt{static_cast<int>(opacity * 255)};

        SDL_SetTextureAlphaMod(image.get(), opacityInt);

        if (blendMode != SDL_BLENDMODE_NONE) {
            SDL_SetTextureBlendMode(image.get(), blendMode);
        }

        SDL_RenderCopyEx(_<SDL8DEVICE>().mRenderer.get(), image.get(), nullptr,
                         &rect, 0, nullptr, flip);

        SDL_SetTextureAlphaMod(image.get(), 255);

        if (blendMode != SDL_BLENDMODE_NONE) {
            SDL_SetTextureBlendMode(image.get(), SDL_BLENDMODE_NONE);
        }
    }

    void
    IMAGE8RENDERER::DRAW8IMAGE(std::string_view imageName, float x, float y,
                               float width, float height, float opacity,
                               bool flipHorizontal, SDL_BlendMode blendMode) {
        auto hash{HASH(imageName)};

        DRAW8IMAGE(hash, x, y, width, height, opacity, flipHorizontal,
                   blendMode);
    }

    void
    IMAGE8RENDERER::DRAW8IMAGE(int imageNameHash, RECT8F bounds, float opacity,
                               bool flipHorizontal, SDL_BlendMode blendMode) {
        DRAW8IMAGE(imageNameHash, bounds.x, bounds.y, bounds.width,
                   bounds.height, opacity, flipHorizontal, blendMode);
    }

    void
    IMAGE8RENDERER::DRAW8IMAGE(std::string_view imageName, RECT8F bounds,
                               float opacity, bool flipHorizontal,
                               SDL_BlendMode blendMode) {
        DRAW8IMAGE(imageName, bounds.x, bounds.y, bounds.width, bounds.height,
                   opacity, flipHorizontal, blendMode);
    }

    void
    IMAGE8RENDERER::DRAW8IMAGE8AUTOSIZE(std::string_view imageName, float x,
                                        float y, float width, float opacity,
                                        bool flipHorizontal,
                                        SDL_BlendMode blendMode) {
        auto hash{HASH(imageName)};
        auto imageSize{_<IMAGE8BANK>().GET8IMAGE8SIZE(hash)};
        auto height{CONVERT8WIDTH8TO8HEIGHT(imageSize.height * width /
                                            imageSize.width)};

        DRAW8IMAGE(imageName, x, y, width, height, opacity, flipHorizontal,
                   blendMode);
    }
}