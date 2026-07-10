#include "stdafx.h"
#include "ColoredPlanksTile.h"
#include "net.minecraft.world.h"

const wstring ColoredPlanksTile::TEXTURE_NAMES[] = {L"planks_white", L"planks_silver", L"planks_gray", L"planks_black", L"planks_brown", L"planks_red", L"planks_orange", L"planks_yellow", L"planks_lime", L"planks_green", L"planks_cyan", L"planks_light_blue", L"planks_blue", L"planks_purple", L"planks_magenta", L"planks_pink"};

const unsigned int ColoredPlanksTile::COLORED_PLANK_NAMES[COLORED_PLANK_NAMES_LENGTH] = {
	IDS_TILE_COLORED_PLANKS_WHITE,
	IDS_TILE_COLORED_PLANKS_SILVER,
	IDS_TILE_COLORED_PLANKS_GRAY,
	IDS_TILE_COLORED_PLANKS_BLACK,
	IDS_TILE_COLORED_PLANKS_BROWN,
	IDS_TILE_COLORED_PLANKS_RED,
	IDS_TILE_COLORED_PLANKS_ORANGE,
	IDS_TILE_COLORED_PLANKS_YELLOW,
	IDS_TILE_COLORED_PLANKS_LIME,
	IDS_TILE_COLORED_PLANKS_GREEN,
	IDS_TILE_COLORED_PLANKS_CYAN,
	IDS_TILE_COLORED_PLANKS_LIGHTBLUE,
	IDS_TILE_COLORED_PLANKS_BLUE,
	IDS_TILE_COLORED_PLANKS_PURPLE,
	IDS_TILE_COLORED_PLANKS_MAGENTA,
	IDS_TILE_COLORED_PLANKS_PINK,
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
