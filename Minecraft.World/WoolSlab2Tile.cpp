#include "stdafx.h"
#include "net.minecraft.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.h"
#include "WoolSlab2Tile.h"

const unsigned int WoolSlab2Tile::SLAB_NAMES[SLAB_NAMES_LENGTH] =
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

WoolSlab2Tile::WoolSlab2Tile(int id, bool fullSize) : HalfSlabTile(id, fullSize, Material::stone)
{
}

Icon *WoolSlab2Tile::getTexture(int face, int data)
{
	int type = data & TYPE_MASK;
	if (fullSize && (data & TOP_SLOT_BIT) != 0)
	{
		face = Facing::UP;
	}
	switch(type)
	{
	case LIME:
		return Tile::wool->getTexture(face, 5);
	case GREEN:
		return Tile::wool->getTexture(face, 13);
	case CYAN:
		return Tile::wool->getTexture(face, 9);
	case LIGHT_BLUE:
		return Tile::wool->getTexture(face, 3);
	case BLUE:
		return Tile::wool->getTexture(face, 11);
	case PURPLE:
		return Tile::wool->getTexture(face, 10);
	case MAGENTA:
		return Tile::wool->getTexture(face, 2);
	case PINK:
		return Tile::wool->getTexture(face, 6);
	}
	return icon;
}

void WoolSlab2Tile::registerIcons(IconRegister *iconRegister)
{
	icon = iconRegister->registerIcon(L"wool_colored_lime");
}

int WoolSlab2Tile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Tile::woolSlab2Half_Id;
}

unsigned int WoolSlab2Tile::getDescriptionId(int iData /*= -1*/)
{
	if(iData < 0 ) iData = 0;
	return WoolSlab2Tile::SLAB_NAMES[iData];
}

int WoolSlab2Tile::getAuxName(int auxValue) 
{
	if (auxValue < 0 || auxValue >= SLAB_NAMES_LENGTH) 
	{
		auxValue = 0;
	}
	return SLAB_NAMES[auxValue];
}

shared_ptr<ItemInstance> WoolSlab2Tile::getSilkTouchItemInstance(int data)
{
	return std::make_shared<ItemInstance>(Tile::woolSlab2Half_Id, 2, data & TYPE_MASK);
}
