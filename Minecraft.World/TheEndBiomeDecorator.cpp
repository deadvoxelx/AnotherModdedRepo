#include "stdafx.h"
#include "TheEndBiomeDecorator.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "net.minecraft.world.entity.boss.enderdragon.h"

TheEndBiomeDecorator::TheEndBiomeDecorator(Biome *biome) : BiomeDecorator(biome)
{
	spikeFeature = new SpikeFeature(Tile::endStone_Id);
	endPodiumFeature = new EndPodiumFeature(Tile::endStone_Id);
}

void TheEndBiomeDecorator::decorate()
{
	decorateOres();

	// this will only set the y to the top y of the chunks already processed...
	int y = level->getTopSolidBlock(xo+8, zo+8);
	if(y>level->GetHighestY()) level->SetHighestY(y);

	bool center = (xo == -16 || xo == 0) && (zo == -16 || zo == 0);
	if (!center && random->nextInt(7) == 0)
	{
		int radius = random->nextInt(3) + 1;
		int x = xo + radius + random->nextInt(16 - 2 * radius);
		int z = zo + radius + random->nextInt(16 - 2 * radius);

		bool ground = true;

		for (int xx = x - radius; xx <= x + radius && ground; xx++)
		{
			for (int zz = z - radius; zz <= z + radius; zz++)
			{
				int xd = xx - x;
				int zd = zz - z;
				if (xd * xd + zd * zd <= radius * radius + 1 && level->getTopSolidBlock(xx, zz) <= 0)
				{
					ground = false;
					break;
				}
			}
		}

		if (ground)
		{
		    int index = random->nextInt(8);
		    spikeFeature->placeWithIndex(level, random, x, level->getTopSolidBlock(x, z), z, index, radius);
		}
	}
	if (xo == 0 && zo == 0)
	{
		shared_ptr<EnderDragon> enderDragon = std::make_shared<EnderDragon>(level);
		enderDragon->AddParts();		// 4J added
		enderDragon->moveTo(0, 128, 0, random->nextFloat() * 360, 0);
		level->addEntity(enderDragon);
	}

	// end podium radius is 4, position is 0,0, so chunk needs to be the -16,-16 one since this guarantees that all chunks required for the podium are loaded
	if (xo == -16 && zo == -16)
	{		
		endPodiumFeature->place(level, random, 0, level->seaLevel, 0);
	}
}
