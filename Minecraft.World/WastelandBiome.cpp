#include "stdafx.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.level.biome.h"
#include "WastelandBiome.h"

WastelandBiome::WastelandBiome(int id) : Biome(id)
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

void WastelandBiome::decorate(Level *level, Random *random, int xo, int zo)
{
	Biome::decorate(level, random, xo, zo);

	PIXBeginNamedEvent(0,"Lava");
	if (random->nextInt(8) == 0)
	{
		int x = xo + random->nextInt(16) + 8;
		int y = random->nextInt(Level::genDepth);
		int z = zo + random->nextInt(16) + 8;

		LakeFeature calmLava(Tile::calmLava_Id);
		calmLava.place(level, random, x, y, z);
	}
	PIXEndNamedEvent();

	if (random->nextInt(250) == 0)
	{
		int x = xo + random->nextInt(16) + 8;
		int z = zo + random->nextInt(16) + 8;
		Feature *well = new DesertWellFeature();
		well->place(level, random, x, level->getHeightmap(x, z) + 1, z);
	}

	OreFeature dryDirtFeature(Tile::dirt_Id, 1, 32, Tile::sand_Id);
	for (int i = 0; i < 28; i++)
	{
		int x = xo + random->nextInt(16);
		int y = 63 + random->nextInt(64);
		int z = zo + random->nextInt(16);
		dryDirtFeature.place(level, random, x, y, z);
	}

	PIXBeginNamedEvent(0, "Dead Trees");
	DeadTreeFeature *deadTree = new DeadTreeFeature(false);

	for (int i = 0; i < 12; i++)
	{
		int x = xo + random->nextInt(16) + 8;
		int y = 63 + random->nextInt(64);
		int z = zo + random->nextInt(16) + 8;
		deadTree->place(level, random, x, y, z);
	}
	PIXEndNamedEvent();
}