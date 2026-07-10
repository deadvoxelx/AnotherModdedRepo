#include "stdafx.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "CherryTreeFeature.h"

CherryTreeFeature::CherryTreeFeature(bool doUpdate) : Feature(doUpdate), baseHeight(4)
{
}

CherryTreeFeature::CherryTreeFeature(bool doUpdate, int baseHeight) : Feature(doUpdate), baseHeight(baseHeight)
{
}

bool CherryTreeFeature::place(Level *level, Random *random, int x, int y, int z)
{
	int treeHeight = random->nextInt(3) + baseHeight;

	bool free = true;
	if (y < 1 || y + treeHeight + 1 > Level::maxBuildHeight) return false;

	if (app.getLevelGenerationOptions() != NULL)
	{
		PIXBeginNamedEvent(0, "CherryTreeFeature checking intersects");
		LevelGenerationOptions *levelGenOptions = app.getLevelGenerationOptions();
		bool intersects = levelGenOptions->checkIntersects(x - 2, y - 1, z - 2, x + 2, y + treeHeight, z + 2);
		PIXEndNamedEvent();
		if (intersects)
		{
			return false;
		}
	}

	for (int yy = y; yy <= y + 1 + treeHeight; yy++)
	{
		int r = 1;
		if (yy == y) r = 0;
		if (yy >= y + 1 + treeHeight - 2) r = 2;
		for (int xx = x - r; xx <= x + r && free; xx++)
		{
			for (int zz = z - r; zz <= z + r && free; zz++)
			{
				if (yy >= 0 && yy < Level::maxBuildHeight)
				{
					int tt = level->getTile(xx, yy, zz);
					if (tt != 0 && tt != Tile::leaves_Id && tt != Tile::leaves2_Id && tt != Tile::grass_Id && tt != Tile::dirt_Id && tt != Tile::treeTrunk_Id && tt != Tile::cherryLog_Id) free = false;
				}
				else
				{
					free = false;
				}
			}
		}
	}

	if (!free) return false;

	int belowTile = level->getTile(x, y - 1, z);
	if ((belowTile != Tile::grass_Id && belowTile != Tile::dirt_Id) || y >= Level::maxBuildHeight - treeHeight - 1) return false;

	placeBlock(level, x, y - 1, z, Tile::dirt_Id);

	PIXBeginNamedEvent(0, "Placing CherryTreeFeature leaves");
	int grassHeight = 3;
	int extraWidth = 0;
	for (int yy = y + treeHeight; yy >= y - grassHeight + treeHeight; yy--)
	{
		int yo = yy - (y + treeHeight);
		int offs = extraWidth + 1 - yo / 2;
		for (int xx = x - offs; xx <= x + offs; xx++)
		{
			int xo = xx - (x);
			for (int zz = z - offs; zz <= z + offs; zz++)
			{
				int zo = zz - (z);
				if (abs(xo) == offs && abs(zo) == offs && (random->nextInt(2) == 0 || yo == 0)) continue;
				if (!Tile::solid[level->getTile(xx, yy, zz)]) placeBlock(level, xx, yy, zz, Tile::leaves2_Id, 0);
			}
		}
	}
	PIXEndNamedEvent();

	PIXBeginNamedEvent(0, "Placing CherryTreeFeature trunks");
	for (int hh = 0; hh < treeHeight; hh++)
	{
		int t = level->getTile(x, y + hh, z);
		if (t == 0 || t == Tile::leaves_Id || t == Tile::leaves2_Id)
		{
			placeBlock(level, x, y + hh, z, Tile::cherryLog_Id, 0);
		}
	}
	PIXEndNamedEvent();

	return true;
}