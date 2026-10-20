// Copyright (c) 2026 Andreas Åkerberg
// SPDX-License-Identifier: MIT

#include "GUI_EQUIPMENT_WINDOW.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER.HPP"
#include "CORE/CORE_GAME_OBJECTS/PLAYER_EQUIPMENT.HPP"
#include "CORE/RENDERING/IMAGES/IMAGE_RENDERER.HPP"
#include "CORE/WORLD_STRUCTURE/OBJECT.HPP"
#include "THEME_0/SCENES/MAIN/SUB/OBJECT_MOVING.HPP"

GUIEquipmentWindow::GUIEquipmentWindow()
    : GUIWindow("Equipment", 0.45f, 0.3f, 0.2f, 0.4f)
{
}

bool GUIEquipmentWindow::OnMouseDown(Uint8 mouseButton)
{
    auto result = GUIWindow::OnMouseDown(mouseButton);

    auto mousePosition = GET8MOUSE8POSITION();

    if (GetHeadSlotBounds().CONTAINS(mousePosition))
    {
        _<ObjectMoving>().SetObjectInAir(
            _<Player>().playerEquipment_->headObject_);

        _<Player>().playerEquipment_->headObject_ = nullptr;

        return true;
    }
    else if (GetChestSlotBounds().CONTAINS(mousePosition))
    {
        _<ObjectMoving>().SetObjectInAir(
            _<Player>().playerEquipment_->chestObject_);

        _<Player>().playerEquipment_->chestObject_ = nullptr;

        return true;
    }
    else if (GetLegsSlotBounds().CONTAINS(mousePosition))
    {
        _<ObjectMoving>().SetObjectInAir(
            _<Player>().playerEquipment_->legsObject_);

        _<Player>().playerEquipment_->legsObject_ = nullptr;

        return true;
    }
    else if (GetFeetSlotBounds().CONTAINS(mousePosition))
    {
        _<ObjectMoving>().SetObjectInAir(
            _<Player>().playerEquipment_->feetObject_);

        _<Player>().playerEquipment_->feetObject_ = nullptr;

        return true;
    }
    else if (GetRightHandSlotBounds().CONTAINS(mousePosition))
    {
        _<ObjectMoving>().SetObjectInAir(
            _<Player>().playerEquipment_->rightHandObject_);

        _<Player>().playerEquipment_->rightHandObject_ = nullptr;

        return true;
    }
    else if (GetLeftHandSlotBounds().CONTAINS(mousePosition))
    {
        _<ObjectMoving>().SetObjectInAir(
            _<Player>().playerEquipment_->leftHandObject_);

        _<Player>().playerEquipment_->leftHandObject_ = nullptr;

        return true;
    }

    return result;
}

bool GUIEquipmentWindow::OnMouseUp(Uint8 mouseButton, int clickSpeed)
{
    GUIWindow::OnMouseUp(mouseButton, clickSpeed);

    auto mousePosition = GET8MOUSE8POSITION();

    if (GetHeadSlotBounds().CONTAINS(mousePosition))
    {
        _<Player>().playerEquipment_->headObject_ =
            _<ObjectMoving>().GetObjectInAir();

        _<ObjectMoving>().ClearObject();
    }
    else if (GetChestSlotBounds().CONTAINS(mousePosition))
    {
        _<Player>().playerEquipment_->chestObject_ =
            _<ObjectMoving>().GetObjectInAir();

        _<ObjectMoving>().ClearObject();
    }
    else if (GetLegsSlotBounds().CONTAINS(mousePosition))
    {
        _<Player>().playerEquipment_->legsObject_ =
            _<ObjectMoving>().GetObjectInAir();

        _<ObjectMoving>().ClearObject();
    }
    else if (GetFeetSlotBounds().CONTAINS(mousePosition))
    {
        _<Player>().playerEquipment_->feetObject_ =
            _<ObjectMoving>().GetObjectInAir();

        _<ObjectMoving>().ClearObject();
    }
    else if (GetRightHandSlotBounds().CONTAINS(mousePosition))
    {
        _<Player>().playerEquipment_->rightHandObject_ =
            _<ObjectMoving>().GetObjectInAir();

        _<ObjectMoving>().ClearObject();
    }
    else if (GetLeftHandSlotBounds().CONTAINS(mousePosition))
    {
        _<Player>().playerEquipment_->leftHandObject_ =
            _<ObjectMoving>().GetObjectInAir();

        _<ObjectMoving>().ClearObject();
    }

    return false;
}

void GUIEquipmentWindow::RenderDerived()
{
    GUIWindow::RenderDerived();

    auto headBounds = GetHeadSlotBounds();
    auto chestBounds = GetChestSlotBounds();
    auto legsBounds = GetLegsSlotBounds();
    auto feetBounds = GetFeetSlotBounds();
    auto rightHandBounds = GetRightHandSlotBounds();
    auto leftHandBounds = GetLeftHandSlotBounds();

    _<ImageRenderer>().DrawImage(k_headSlotImage_, headBounds);
    _<ImageRenderer>().DrawImage(k_chestSlotImage_, chestBounds);
    _<ImageRenderer>().DrawImage(k_legsSlotImage_, legsBounds);
    _<ImageRenderer>().DrawImage(k_feetSlotImage_, feetBounds);
    _<ImageRenderer>().DrawImage(k_rightHandSlotImage_, rightHandBounds);
    _<ImageRenderer>().DrawImage(k_leftHandSlotImage_, leftHandBounds);

    if (_<Player>().playerEquipment_->headObject_)
    {
        _<ImageRenderer>().DrawImage(
            _<Player>().playerEquipment_->headObject_->type_, headBounds);
    }
    if (_<Player>().playerEquipment_->chestObject_)
    {
        _<ImageRenderer>().DrawImage(
            _<Player>().playerEquipment_->chestObject_->type_, chestBounds);
    }
    if (_<Player>().playerEquipment_->legsObject_)
    {
        _<ImageRenderer>().DrawImage(
            _<Player>().playerEquipment_->legsObject_->type_, legsBounds);
    }
    if (_<Player>().playerEquipment_->feetObject_)
    {
        _<ImageRenderer>().DrawImage(
            _<Player>().playerEquipment_->feetObject_->type_, feetBounds);
    }
    if (_<Player>().playerEquipment_->rightHandObject_)
    {
        _<ImageRenderer>().DrawImage(
            _<Player>().playerEquipment_->rightHandObject_->type_,
            rightHandBounds);
    }
    if (_<Player>().playerEquipment_->leftHandObject_)
    {
        _<ImageRenderer>().DrawImage(
            _<Player>().playerEquipment_->leftHandObject_->type_,
            leftHandBounds);
    }
}

RECT8F GUIEquipmentWindow::GetHeadSlotBounds()
{
    auto position = GetPosition();

    auto xCenter = size_.width / 2.0f;
    auto yCenter = size_.height / 5.0f * 1;

    auto width = k_slotWidth_;
    auto height = CONVERT8WIDTH8TO8HEIGHT(k_slotWidth_);

    auto x = position.x + xCenter - width / 2.0f;
    auto y = position.y + k_marginY_ + yCenter - height / 2.0f;

    return {x, y, width, height};
}

RECT8F GUIEquipmentWindow::GetChestSlotBounds()
{
    auto position = GetPosition();

    auto xCenter = size_.width / 2.0f;
    auto yCenter = size_.height / 5.0f * 2;

    auto width = k_slotWidth_;
    auto height = CONVERT8WIDTH8TO8HEIGHT(k_slotWidth_);

    auto x = position.x + xCenter - width / 2.0f;
    auto y = position.y + k_marginY_ + yCenter - height / 2.0f;

    return {x, y, width, height};
}

RECT8F GUIEquipmentWindow::GetLegsSlotBounds()
{
    auto position = GetPosition();

    auto xCenter = size_.width / 2.0f;
    auto yCenter = size_.height / 5.0f * 3;

    auto width = k_slotWidth_;
    auto height = CONVERT8WIDTH8TO8HEIGHT(k_slotWidth_);

    auto x = position.x + xCenter - width / 2.0f;
    auto y = position.y + k_marginY_ + yCenter - height / 2.0f;

    return {x, y, width, height};
}

RECT8F GUIEquipmentWindow::GetFeetSlotBounds()
{
    auto position = GetPosition();

    auto xCenter = size_.width / 2.0f;
    auto yCenter = size_.height / 5.0f * 4;

    auto width = k_slotWidth_;
    auto height = CONVERT8WIDTH8TO8HEIGHT(k_slotWidth_);

    auto x = position.x + xCenter - width / 2.0f;
    auto y = position.y + k_marginY_ + yCenter - height / 2.0f;

    return {x, y, width, height};
}

RECT8F GUIEquipmentWindow::GetRightHandSlotBounds()
{
    auto position = GetPosition();

    auto xCenter = size_.width / 4.0f * 1;
    auto yCenter = size_.height / 5.0f * 2;

    auto width = k_slotWidth_;
    auto height = CONVERT8WIDTH8TO8HEIGHT(k_slotWidth_);

    auto x = position.x + xCenter - width / 2.0f;
    auto y = position.y + k_marginY_ + yCenter - height / 2.0f;

    return {x, y, width, height};
}

RECT8F GUIEquipmentWindow::GetLeftHandSlotBounds()
{
    auto position = GetPosition();

    auto xCenter = size_.width / 4.0f * 3;
    auto yCenter = size_.height / 5.0f * 2;

    auto width = k_slotWidth_;
    auto height = CONVERT8WIDTH8TO8HEIGHT(k_slotWidth_);

    auto x = position.x + xCenter - width / 2.0f;
    auto y = position.y + k_marginY_ + yCenter - height / 2.0f;

    return {x, y, width, height};
}