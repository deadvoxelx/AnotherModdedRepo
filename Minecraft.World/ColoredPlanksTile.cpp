#include "stdafx.h"
#include "ColoredPlanksTile.h"
#include "net.minecraft.world.h"

const wstring ColoredPlanksTile::TEXTURE_NAMES[] = {L"planks_white", L"planks_silver", L"planks_gray", L"planks_black", L"planks_brown", L"planks_red", L"planks_orange", L"planks_yellow", L"planks_lime", L"planks_green", L"planks_cyan", L"planks_light_blue", L"planks_blue", L"planks_purple", L"planks_magenta", L"planks_pink"};

const unsigned int ColoredPlanksTile::COLORED_PLANK_NAMES[COLORED_PLANK_NAMES_LENGTH] = {
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
	IDS_TILE_COLORED_PLANKS,
};

ColoredPlanksTile::ColoredPlanksTile(int id) : Tile(id, Material::wood)
{
	icons = nullptr;
}

Icon *ColoredPlanksTile::getTexture(int face, int data)
{
	if (data < 0 || data >= COLORED_PLANK_NAMES_LENGTH) data = 0;
	return icons[data];
}

int ColoredPlanksTile::getSpawnResourcesAuxValue(int data)
{
	return data;
}

unsigned int ColoredPlanksTile::getDescriptionId(int iData /*= -1*/)
{
	if(iData < 0 ) iData = 0;
	return ColoredPlanksTile::COLORED_PLANK_NAMES[iData];
}

void ColoredPlanksTile::registerIcons(IconRegister *iconRegister)
{
	icons = new Icon * [COLORED_PLANK_NAMES_LENGTH];

	for (int i = 0; i < COLORED_PLANK_NAMES_LENGTH; i++)
	{
		icons[i] = iconRegister->registerIcon(TEXTURE_NAMES[i]);
	}
}