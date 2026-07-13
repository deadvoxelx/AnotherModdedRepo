#include "stdafx.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.level.biome.h"

DesertBiome::DesertBiome(int id) : Biome(id)
{
	friendlies.clear();
	friendlies_chicken.clear();
	friendlies_wolf.clear();
	topMaterial = static_cast<BYTE>(Tile::sand_Id);
	material = static_cast<BYTE>(Tile::sand_Id);

	decorator->treeCount = -999;
	decorator->deadBushCount = 2;
	decorator->reedsCount = 50;
	decorator->cactusCount = 10;
}

void DesertBiome::decorate(Level *level, Random *random, int xo, int zo)
{
	Biome::decorate(level, random, xo, zo);

	if (random->nextInt(250) == 0)
	{
		int x = xo + random->nextInt(16) + 8;
		int z = zo + random->nextInt(16) + 8;
		Feature *well = new DesertWellFeature();
		well->place(level, random, x, level->getHeightmap(x, z) + 1, z);
	}

	PIXBeginNamedEvent(0, "Palm Trees");
	PalmTreeFeature *palm = new PalmTreeFeature(false);

	for (int i = 0; i < 6; i++)
	{
		int x = xo + random->nextInt(16) + 8;
		int y = 63 + random->nextInt(3);
		int z = zo + random->nextInt(16) + 8;
		palm->place(level, random, x, y, z);
	}
	PIXEndNamedEvent();
}
