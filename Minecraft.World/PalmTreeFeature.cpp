#include "PalmTreeFeature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.material.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.level.tile.h"

PalmTreeFeature::PalmTreeFeature(bool doUpdate) : Feature(doUpdate)
{
}

bool PalmTreeFeature::place(Level *level, Random *random, int x, int y, int z)
{
	int belowTile = level->getTile(x, y - 1, z);
	int baseHeight = 5 + random->nextInt(3);
	int midHeight = 2 + random->nextInt(2);
	int topHeight = 1 + random->nextInt(1);

	if (belowTile != Tile::grass_Id && belowTile != Tile::sand_Id && belowTile != Tile::dirt_Id) return false;

	for (int xx = -8; xx <= 8; xx++)
	{
		for (int zz = -8; zz <= 8; zz++)
		{
			if (level->getBiome(xx, zz)->hasSnow()) return false;
		}
	}

	for (int xy = -4; xy <= 4; xy++)
	{
		for (int yy = 0; yy <= 4; yy++)
		{
			for (int zy = -4; zy <= 4; zy++)
			{
				int thisTile = level->getTile(x + xy, y + yy + 5, z + zy);
				if ((thisTile != 0 && thisTile != Tile::tallgrass_Id && thisTile != Tile::leaves_Id && thisTile != Tile::leaves2_Id)) return false;
			}
		}
	}

	{
		placeBlock(level, x, y - 1, z, Tile::dirt_Id, 0);
			
		for (int trunkbase = 0; trunkbase <= baseHeight; trunkbase++)
		{
			placeBlock(level, x, y + trunkbase, z, Tile::palmLog_Id, 0);
		}
		
		if (random->nextInt(3) == 0)
		{
			for (int trunkmid = 0; trunkmid <= midHeight; trunkmid++)
			{
				placeBlock(level, x + 1, y + baseHeight + 1 + trunkmid, z, Tile::palmLog_Id, 0);
				for (int trunktop = 0; trunktop <= topHeight; trunktop++)
				{
					placeBlock(level, x + 2, y + baseHeight + 1 + midHeight + 1 + trunktop, z, Tile::palmLog_Id, 0);
					foliage(level, random, x + 2, y + baseHeight + 1 + midHeight + topHeight + 1, z);
				}
			}
		}
		else if (random->nextInt(3) == 1)
		{
			for (int trunkmid = 0; trunkmid <= midHeight; trunkmid++)
			{
				placeBlock(level, x - 1, y + baseHeight + 1 + trunkmid, z, Tile::palmLog_Id, 0);
				for (int trunktop = 0; trunktop <= topHeight; trunktop++)
				{
					placeBlock(level, x - 2, y + baseHeight + 1 + midHeight + 1 + trunktop, z, Tile::palmLog_Id, 0);
					foliage(level, random, x - 2, y + baseHeight + 1 + midHeight + topHeight + 1, z);
				}
			}
		}
		else if (random->nextInt(3) == 2)
		{
			for (int trunkmid = 0; trunkmid <= midHeight; trunkmid++)
			{
				placeBlock(level, x, y + baseHeight + 1 + trunkmid, z + 1, Tile::palmLog_Id, 0);
				for (int trunktop = 0; trunktop <= topHeight; trunktop++)
				{
					placeBlock(level, x, y + baseHeight + 1 + midHeight + 1 + trunktop, z + 2, Tile::palmLog_Id, 0);
					foliage(level, random, x, y + baseHeight + 1 + midHeight + topHeight + 1, z + 2);
				}
			}
		}
		else
		{
			for (int trunkmid = 0; trunkmid <= midHeight; trunkmid++)
			{
				placeBlock(level, x, y + baseHeight + 1 + trunkmid, z - 1, Tile::palmLog_Id, 0);
				for (int trunktop = 0; trunktop <= topHeight; trunktop++)
				{
					placeBlock(level, x, y + baseHeight + 1 + midHeight + 1 + trunktop, z - 2, Tile::palmLog_Id, 0);
					foliage(level, random, x, y + baseHeight + 1 + midHeight + topHeight + 1, z - 2);
				}
			}
		}
	}
	return true;
}

bool PalmTreeFeature::foliage(Level* level, Random* random, int x, int y, int z)
{
	for (int blobx = -1; blobx <= 1; blobx++)
	{
		for (int bloby = 0; bloby <= 1; bloby++)
		{
			for (int blobz = -1; blobz <= 1; blobz++)
			{
				if (level->isEmptyTile(x + blobx, y + bloby, z + blobz))
				{
					placeBlock(level, x + blobx, y + bloby, z + blobz, Tile::leaves2_Id, 1);
				}
			}
		}
	}

	for (int leavesx2 = -3; leavesx2 <= 3; leavesx2++)
	{
		placeBlock(level, x + leavesx2, y + 1, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x + leavesx2, y + 1, z - 1, Tile::leaves2_Id, 1);

		placeBlock(level, x + 3, y, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x + 3, y, z - 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 3, y, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 3, y, z - 1, Tile::leaves2_Id, 1);

		placeBlock(level, x + 4, y, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x + 4, y, z - 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 4, y, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 4, y, z - 1, Tile::leaves2_Id, 1);

		placeBlock(level, x + 5, y, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x + 5, y, z - 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 5, y, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 5, y, z - 1, Tile::leaves2_Id, 1);

		placeBlock(level, x + 5, y - 1, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x + 5, y - 1, z - 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 5, y - 1, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 5, y - 1, z - 1, Tile::leaves2_Id, 1);

		placeBlock(level, x + 6, y - 1, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x + 6, y - 1, z - 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 6, y - 1, z + 1, Tile::leaves2_Id, 1);
		placeBlock(level, x - 6, y - 1, z - 1, Tile::leaves2_Id, 1);
	}
	for (int leavesz2 = -3; leavesz2 <= 3; leavesz2++)
	{
		placeBlock(level, x + 1, y + 1, z + leavesz2, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y + 1, z + leavesz2, Tile::leaves2_Id, 1);

		placeBlock(level, x + 1, y, z + 3, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y, z + 3, Tile::leaves2_Id, 1);
		placeBlock(level, x + 1, y, z - 3, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y, z - 3, Tile::leaves2_Id, 1);

		placeBlock(level, x + 1, y, z + 4, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y, z + 4, Tile::leaves2_Id, 1);
		placeBlock(level, x + 1, y, z - 4, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y, z - 4, Tile::leaves2_Id, 1);

		placeBlock(level, x + 1, y, z + 5, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y, z + 5, Tile::leaves2_Id, 1);
		placeBlock(level, x + 1, y, z - 5, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y, z - 5, Tile::leaves2_Id, 1);

		placeBlock(level, x + 1, y - 1, z + 5, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y - 1, z + 5, Tile::leaves2_Id, 1);
		placeBlock(level, x + 1, y - 1, z - 5, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y - 1, z - 5, Tile::leaves2_Id, 1);

		placeBlock(level, x + 1, y - 1, z + 6, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y - 1, z + 6, Tile::leaves2_Id, 1);
		placeBlock(level, x + 1, y - 1, z - 6, Tile::leaves2_Id, 1);
		placeBlock(level, x - 1, y - 1, z - 6, Tile::leaves2_Id, 1);
	}
	return true;
}
