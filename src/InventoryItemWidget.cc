/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright (C) 2005-2007  Guido de Jong <guidoj@users.sf.net>
 */

#include "Exception.h"
#include "InventoryItemWidget.h"
#include "MousePointerManager.h"

InventoryItemWidget::InventoryItemWidget(const Rectangle &r, const int a)
: ActiveWidget(r, a)
, iconImage(0)
, label(0)
, pressed(false)
, selected(false)
{
  SetFocusable(false);
}

InventoryItemWidget::~InventoryItemWidget()
{
  if (label) {
    delete label;
  }
}

void
InventoryItemWidget::SetImage(Image *icon)
{
  if (!icon) {
    throw NullPointer(__FILE__, __LINE__);
  }
  iconImage = icon;
}

void
InventoryItemWidget::SetLabel(const std::string& s, Font *f)
{
  label = new TextWidget(Rectangle(rect.GetXPos(), rect.GetYPos(), rect.GetWidth(), rect.GetHeight()), f);
  label->SetText(s);
  label->SetColor(INFO_TEXT_COLOR);
  label->SetAlignment(HA_RIGHT, VA_BOTTOM);
}

void
InventoryItemWidget::Draw()
{
  if (IsVisible()) {
    if (selected) {
    }
    if ((!pressed) && (iconImage)) {
      iconImage->Draw(rect.GetXPos() + (rect.GetWidth() - iconImage->GetWidth()) / 2,
                      rect.GetYPos() + (rect.GetHeight() - iconImage->GetHeight()) / 2, 0);
    }
    if (label && !pressed) {
      label->Draw();
    }
  }
}

void
InventoryItemWidget::LeftClick(const bool toggle, const int x, const int y)
{
  if (IsVisible()) {
    pressed = toggle;
    MousePointer *mp = MousePointerManager::GetInstance()->GetCurrentPointer();
    if (toggle) {
      mp->SetDragImage(iconImage,
                       rect.GetXPos() + (rect.GetWidth() - iconImage->GetWidth()) / 2 - x,
                       rect.GetYPos() + (rect.GetHeight() - iconImage->GetHeight()) / 2 - y);
      GenerateActionEvent(GetAction());
    } else {
      mp->SetDragImage(0, 0, 0);
      GenerateActionEvent(GetAction());
    }
  }
}

void
InventoryItemWidget::RightClick(const bool toggle, const int, const int)
{
  if (IsVisible()) {
    selected = toggle;
    if (toggle) {
      GenerateActionEvent(GetAction() + RIGHT_CLICK_OFFSET);
    }
  }
}
