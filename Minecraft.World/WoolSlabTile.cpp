#include "stdafx.h"
#include "net.minecraft.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.h"
#include "WoolSlabTile.h"

const unsigned int WoolSlabTile::SLAB_NAMES[SLAB_NAMES_LENGTH] =
{
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
	IDS_TILE_WOOL_SLAB,
};

WoolSlabTile::WoolSlabTile(int id, bool fullSize) : HalfSlabTile(id, fullSize, Material::stone)
{
}

Icon *WoolSlabTile::getTexture(int face, int data)
{
	int type = data & TYPE_MASK;
	if (fullSize && (data & TOP_SLOT_BIT) != 0)
	{
		face = Facing::UP;
	}
	switch(type)
	{
	case WHITE:
		return Tile::wool->getTexture(face, 0);
	case SILVER:
		return Tile::wool->getTexture(face, 8);
	case GRAY:
		return Tile::wool->getTexture(face, 7);
	case BLACK:
		return Tile::wool->getTexture(face, 15);
	case BROWN:
		return Tile::wool->getTexture(face, 12);
	case RED:
		return Tile::wool->getTexture(face, 14);
	case ORANGE:
		return Tile::wool->getTexture(face, 1);
	case YELLOW:
		return Tile::wool->getTexture(face, 4);
	}
	return icon;
}

void WoolSlabTile::registerIcons(IconRegister *iconRegister)
{
	icon = iconRegister->registerIcon(L"wool_colored_white");
}

int WoolSlabTile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Tile::woolSlabHalf_Id;
}

unsigned int WoolSlabTile::getDescriptionId(int iData /*= -1*/)
{
	if(iData < 0 ) iData = 0;
	return WoolSlabTile::SLAB_NAMES[iData];
}

int WoolSlabTile::getAuxName(int auxValue) 
{
	if (auxValue < 0 || auxValue >= SLAB_NAMES_LENGTH) 
	{
		auxValue = 0;
	}
	return SLAB_NAMES[auxValue];
}

shared_ptr<ItemInstance> WoolSlabTile::getSilkTouchItemInstance(int data)
{
	return std::make_shared<ItemInstance>(Tile::woolSlabHalf_Id, 2, data & TYPE_MASK);
}
