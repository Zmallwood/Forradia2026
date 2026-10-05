// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "ObjectMoving.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Core/Configuration/GameProperties.hpp"
#include "Core/Configuration/ObjectIndex.hpp"
#include "Core/CoreGameObjects/Player.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/WorldStructure/Object.hpp"
#include "Core/WorldStructure/Tile.hpp"
#include "Core/WorldStructure/TileObjects.hpp"
#include "Core/WorldStructure/World.hpp"
#include "Core/WorldStructure/WorldArea.hpp"
#include "FirstPersonHovering.hpp"
#include "FirstPersonView/FirstPersonViewFunctions.hpp"

void ObjectMoving::OnMouseDown(Uint8 button)
{
    if (button != SDL_BUTTON_LEFT)
    {
        return;
    }

    auto viewWidth{GameProperties::k_viewWidth_};

    auto mousePosition{GetMousePosition()};

    if (mousePosition.x < viewWidth)
    {
        return;
    }

    auto hoveredObject{_<FirstPersonHovering>().hoveredObject_};

    if (!hoveredObject)
    {
        return;
    }

    if (_<ObjectIndex>().ObjectUnmovable(hoveredObject->type_))
    {
        return;
    }

    auto worldArea{_<World>().currentWorldArea_};

    auto facedTileCoordinate{_<Player>().facedTileCoordinate_};

    auto tile{worldArea->GetTile(facedTileCoordinate)};

    objectInAir_ = tile->tileObjects_->PickObject(hoveredObject);

    draggingMouseOffset_ = _<FirstPersonHovering>().hoveredThingMouseOffset_;

    pickedPosition_ = GetHoveredTilePosition(draggingMouseOffset_);
}

void ObjectMoving::OnMouseUp(Uint8 button, int clickSpeed)
{
    if (!objectInAir_)
    {
        return;
    }

    if (button != SDL_BUTTON_LEFT)
    {
        return;
    }

    auto viewWidth{GameProperties::k_viewWidth_};

    auto mousePosition{GetMousePosition()};

    auto hoveredTilePosition{GetHoveredTilePosition(draggingMouseOffset_)};

    if (mousePosition.x < viewWidth)
    {
        hoveredTilePosition = pickedPosition_;
    }

    if (hoveredTilePosition == Point{-1, -1})
    {
        hoveredTilePosition = pickedPosition_;
    }

    auto worldArea{_<World>().currentWorldArea_};

    auto facedTileCoordinate{_<Player>().facedTileCoordinate_};

    auto tile{worldArea->GetTile(facedTileCoordinate)};

    tile->tileObjects_->AddObject(objectInAir_, hoveredTilePosition);

    ClearObject();
}

void ObjectMoving::Render()
{
    if (!objectInAir_)
    {
        return;
    }

    auto mousePosition{GetMousePosition()};

    auto objectType{objectInAir_->type_};

    auto imageSize{_<ImageBank>().GetImageSize(objectType)};

    constexpr auto largeObjectScale{GameProperties::k_largeObjectScale_};
    constexpr auto smallObjectScale{GameProperties::k_smallObjectScale_};

    auto isSmallObject{_<ObjectIndex>().IsSmallObject(objectType)};

    auto scale{isSmallObject ? smallObjectScale : largeObjectScale};

    auto imageWidth{imageSize.width / 60.0f * scale};
    auto imageHeight{imageSize.height / 60.0f * ConvertWidthToHeight(scale)};

    auto imageX{mousePosition.x - draggingMouseOffset_.x - imageWidth / 2.0f};
    auto imageY{mousePosition.y - draggingMouseOffset_.y - imageHeight};

    _<ImageRenderer>().DrawImage(objectType, imageX, imageY, imageWidth,
                                 imageHeight);
}

void ObjectMoving::ClearObject()
{
    objectInAir_ = nullptr;

    draggingMouseOffset_ = {0.0f, 0.0f};
}