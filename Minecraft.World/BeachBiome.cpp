#include "stdafx.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "BiomeDecorator.h"
#include "BeachBiome.h"

BeachBiome::BeachBiome(int id) : Biome(id)
{
	friendlies.clear();
	friendlies_chicken.clear();
	topMaterial = static_cast<byte>(Tile::sand_Id);
	material = static_cast<byte>(Tile::sand_Id);

	decorator->treeCount = -999;
	decorator->deadBushCount = 0;
	decorator->reedsCount = 0;
	decorator->cactusCount = 0;
}

void BeachBiome::decorate(Level *level, Random *random, int xo, int zo)
{
	Biome::decorate(level, random, xo, zo);

	PIXBeginNamedEvent(0, "Palm Trees");
	PalmTreeFeature *palm = new PalmTreeFeature(false);

	for (int i = 0; i < 12; i++)
	{
		int x = xo + random->nextInt(16) + 8;
		int y = 63 + random->nextInt(3);
		int z = zo + random->nextInt(16) + 8;
		palm->place(level, random, x, y, z);
	}
	PIXEndNamedEvent();
}
