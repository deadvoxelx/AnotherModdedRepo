#include "stdafx.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.entity.animal.h"
#include "net.minecraft.world.entity.h"
#include "BirchBiome.h"

BirchBiome::BirchBiome(int id) : Biome(id)
{
	friendlies_wolf.push_back(new MobSpawnerData(eTYPE_WOLF, 5, 4, 4));
	decorator->treeCount = 10;
	decorator->grassCount = 3;
}

Feature *BirchBiome::getTreeFeature(Random *random)
{
	return new BirchFeature(false);
}