#include "stdafx.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.entity.animal.h"
#include "net.minecraft.world.entity.h"
#include "ForestBiome.h"

ForestBiome::ForestBiome(int id) : Biome(id)
{
	friendlies_wolf.push_back(new MobSpawnerData(eTYPE_WOLF, 5, 4, 4));
	decorator->treeCount = 10;
	decorator->grassCount = 2;
}

Feature *ForestBiome::getTreeFeature(Random *random)
{
    if (random->nextInt(5) == 0)
	{
        return new BirchFeature(false); // 4J used to return member birchTree, now returning newly created object so that caller can be consistently resposible for cleanup
    }
    if (random->nextInt(10) == 0)
	{
        return new BasicTree(false); // 4J used to return member fancyTree, now returning newly created object so that caller can be consistently resposible for cleanup
    }
    return new TreeFeature(false); // 4J used to return member normalTree, now returning newly created object so that caller can be consistently resposible for cleanup
}

void ForestBiome::decorate(Level *level, Random *random, int xo, int zo)
{
	Biome::decorate(level, random, xo, zo);

	PIXBeginNamedEvent(0, "Rare Cherry Trees");
	CherryTreeFeature *cherry = new CherryTreeFeature(false);

	for (int i = 0; i < 20; i++)
	{
		int x = xo + random->nextInt(16) + 8;
		int y = 92 + random->nextInt(32);
		int z = zo + random->nextInt(16) + 8;
		cherry->place(level, random, x, y, z);
	}
	PIXEndNamedEvent();
}
