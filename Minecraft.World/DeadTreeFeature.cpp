#include "DeadTreeFeature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.material.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.level.tile.h"

DeadTreeFeature::DeadTreeFeature(bool doUpdate) : Feature(doUpdate)
{
}

bool DeadTreeFeature::place(Level *level, Random *random, int x, int y, int z)
{
	int belowTile = level->getTile(x, y - 1, z);
    int thisTile = level->getTile(x, y, z);
	int baseHeight = 5 + random->nextInt(4);

	if ((belowTile == Tile::grass_Id || belowTile == Tile::sand_Id || belowTile == Tile::dirt_Id) && (thisTile == 0 || thisTile == Tile::tallgrass_Id || thisTile == Tile::leaves_Id || thisTile == Tile::leaves2_Id))
	{
		placeBlock(level, x, y - 1, z, Tile::dirt_Id, 0);
			
		for (int trunkbase = 0; trunkbase <= baseHeight; trunkbase++)
		{
			placeBlock(level, x, y + trunkbase, z, Tile::deadLog_Id, 0);
		}
	}
    return true;
}