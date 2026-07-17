#include "stdafx.h"
#include "BrickTile.h"
#include "net.minecraft.world.h"
#include "net.minecraft.h"

const unsigned int BrickTile::BRICK_NAMES[BRICK_NAMES_LENGTH] = {
	IDS_TILE_BRICK,
	IDS_TILE_BRICK,
	IDS_TILE_BRICK,
	IDS_TILE_BRICK,
};

const wstring BrickTile::TEXTURE_NAMES[] = {
	L"brick", L"brickStone", L"brickLimestone", L"brickGranite"
};

BrickTile::BrickTile(int id) : Tile(id, Material::stone)
{
	icons = nullptr;
}

int BrickTile::getSpawnResourcesAuxValue(int data)
{
	return data;
}

Icon* BrickTile::getTexture(int face, int data)
{
	if (data < 0 || data >= BRICK_NAMES_LENGTH)
	{
		data = 0;
	}
	return icons[data];
}

void BrickTile::registerIcons(IconRegister* iconRegister)
{
	icons = new Icon * [BRICK_NAMES_LENGTH];

	for (int i = 0; i < BRICK_NAMES_LENGTH; i++)
	{
		icons[i] = iconRegister->registerIcon(TEXTURE_NAMES[i]);
	}
}