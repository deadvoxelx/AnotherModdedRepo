#include "PalmTreeFeature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.material.h"
#include "net.minecraft.world.level.tile.h"

PalmTreeFeature::PalmTreeFeature(bool doUpdate) : Feature(doUpdate)
{
}

bool PalmTreeFeature::place(Level *level, Random *random, int x, int y, int z)
{
	int belowTile = level->getTile(x, y - 1, z);
    int thisTile = level->getTile(x, y, z);
	int baseHeight = 5 + random->nextInt(3);
	int midHeight = 2 + random->nextInt(2);
	int topHeight = 1 + random->nextInt(1);

	if ((belowTile == Tile::grass_Id || belowTile == Tile::sand_Id || belowTile == Tile::dirt_Id) && (thisTile == 0 || thisTile == Tile::tallgrass_Id || thisTile == Tile::leaves_Id || thisTile == Tile::leaves2_Id))
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
		else if (random->nextInt(3) == 3)
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
	int baseHeight = 5 + random->nextInt(3);
	int midHeight = 2 + random->nextInt(2);
	int topHeight = 1 + random->nextInt(1);

	for (int leavesx = -6; leavesx <= 6; leavesx++)
	{
		for (int leavesy = -2; leavesy <= 2; leavesy++)
		{
			for (int leavesz = -6; leavesz <= 6; leavesz++)
			{
				for (int blobx = -1; blobx <= 1; blobx++)
				{
					for (int bloby = 0; bloby <= 1; bloby++)
					{
						for (int blobz = -1; blobz <= 1; blobz++)
						{
							int blob = level->getTile(x + blobx, y + bloby, z + blobz);
							if (blob == 0 || blob == Tile::leaves_Id || blob == Tile::leaves2_Id)
							{
								placeBlock(level, x + blobx, y + bloby, z + blobz, Tile::leaves2_Id, 1);
							}
						}
					}
				}

				int flow = level->getTile(x + leavesx, y + leavesy, z + leavesz);
				if (flow == 0 || flow == Tile::leaves_Id || flow == Tile::leaves2_Id)
				{
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
				}
			}
		}
	}
	return true;
}