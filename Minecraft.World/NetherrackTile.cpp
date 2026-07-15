#include "stdafx.h"
#include "NetherrackTile.h"
#include "net.minecraft.world.h"
#include "net.minecraft.h"

const unsigned int NetherrackTile::NETHERRACK_NAMES[NETHERRACK_NAMES_LENGTH] = {
	IDS_TILE_NETHERRACK,
	IDS_TILE_HELL_ROCK,
};

const wstring NetherrackTile::TEXTURE_NAMES[] = {
	L"netherrack", L"netherrackSmooth"
};

NetherrackTile::NetherrackTile(int id) : Tile(id, Material::stone)
{
	icons = nullptr;
}

int NetherrackTile::getSpawnResourcesAuxValue(int data)
{
	return data;
}

Icon* NetherrackTile::getTexture(int face, int data)
{
	if (data < 0 || data >= NETHERRACK_NAMES_LENGTH)
	{
		data = 0;
	}
	return icons[data];
}

void NetherrackTile::registerIcons(IconRegister* iconRegister)
{
	icons = new Icon * [NETHERRACK_NAMES_LENGTH];

	for (int i = 0; i < NETHERRACK_NAMES_LENGTH; i++)
	{
		icons[i] = iconRegister->registerIcon(TEXTURE_NAMES[i]);
	}
}
