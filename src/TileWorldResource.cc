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
 * Copyright (C) 2005-2006  Guido de Jong <guidoj@users.sf.net>
 */

#include "Exception.h"
#include "TileWorldResource.h"

TileWorldResource::TileWorldResource()
: xCenter(0)
, yCenter(0)
, items()
{
}

TileWorldResource::~TileWorldResource()
{
  Clear();
}

unsigned int
TileWorldResource::GetMinX() const
{
  return xCenter - TILE_SIZE_2;
}

unsigned int
TileWorldResource::GetMaxX() const
{
 return xCenter + TILE_SIZE_2;
}

unsigned int
TileWorldResource::GetMinY() const
{
  return yCenter - TILE_SIZE_2;
}

unsigned int
TileWorldResource::GetMaxY() const
{
  return yCenter + TILE_SIZE_2;
}

unsigned int
TileWorldResource::GetSize() const
{
  return items.size();
}

TileWorldItem&
TileWorldResource::GetItem(unsigned int i)
{
  return items[i];
}

void
TileWorldResource::Clear()
{
  items.clear();
}

void
TileWorldResource::Load(FileBuffer *buffer)
{
  try {
    Clear();
    while (!buffer->AtEnd()) {
      TileWorldItem twi;
      twi.type = buffer->GetUint32LE();
      twi.flags = buffer->GetUint32LE();
      twi.xloc = buffer->GetUint32LE();
      twi.yloc = buffer->GetUint32LE();
      if (twi.type == OBJECT_CENTER) {
        xCenter = twi.xloc;
        yCenter = twi.yloc;
      }
      items.push_back(twi);
      buffer->Skip(4);
    }
  } catch (Exception &e) {
    e.Print("TileWorldResource::Load");
    throw;
  }
}

void
TileWorldResource::Save(FileBuffer *buffer)
{
  try {
    // TODO
    buffer = buffer;
  } catch (Exception &e) {
    e.Print("TileWorldResource::Save");
    throw;
  }
}
