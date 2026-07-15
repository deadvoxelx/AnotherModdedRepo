#include "stdafx.h"
#include "StoneTile.h"

StoneTile::StoneTile(int id) : Tile(id, Material::stone)
{
}

int StoneTile::getResource(int data, Random *random, int playerBonusLevel)
{
	if (id == Tile::limestone_Id)
	{
		return Tile::limestoneCobbled_Id;
	}
	if (id == Tile::granite_Id)
	{
		return Tile::graniteCobbled_Id;
	}
	return Tile::cobblestone_Id;
}
