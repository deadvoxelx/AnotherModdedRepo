#include "stdafx.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.entity.animal.h"
#include "net.minecraft.world.entity.h"
#include "CherryBiome.h"

CherryBiome::CherryBiome(int id) : Biome(id)
{
	decorator->treeCount = 10;
	decorator->grassCount = 2;
    decorator->flowerCount = 5;
}

Feature *CherryBiome::getTreeFeature(Random *random)
{
    if (random->nextInt(7) == 0)
	{
        return new TreeFeature(false);
    }
    if (random->nextInt(5) == 0)
	{
        return new CherryTreeLarge(false);
    }
    return new CherryTreeFeature(false);
}