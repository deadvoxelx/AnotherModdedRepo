#include "stdafx.h"
#include "SaplingNew.h"
#include "CherryTreeFeature.h"
#include "CherryTreeLarge.h"
#include "SwampTreeFeature.h"
#include "PalmTreeFeature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.h"

SaplingNewTile::SaplingNewTile(int id) : Bush(id)
{
	this->updateDefaultShape();
}

void SaplingNewTile::updateDefaultShape()
{
	float ss = 0.4f;
	this->setShape(0.5f - ss, 0, 0.5f - ss, 0.5f + ss, 0.8f, 0.5f + ss);
}

void SaplingNewTile::tick(Level *level, int x, int y, int z, Random *random)
{
	if (level->isClientSide) return;

	Bush::tick(level, x, y, z, random);

	if (level->getRawBrightness(x, y + 1, z) >= Level::MAX_BRIGHTNESS - 6)
	{
		if (random->nextInt(7) == 0)
		{
			int data = level->getData(x, y, z);
			if ((data & AGE_BIT) == 0)
			{
				level->setData(x, y, z, data | AGE_BIT, false);
			}
			else
			{
				growTree(level, x, y, z, random);
			}
		}
	}
}

void SaplingNewTile::growTree(Level *level, int x, int y, int z, Random *random)
{
	Feature *f = nullptr;

	if (this->id == Tile::palmSapling_Id)
	{
		f = new PalmTreeFeature(false);
	}
	else if (this->id == Tile::mossySapling_Id)
	{
		f = new SwampTreeFeature();
	}
	else if (this->id == Tile::cherrySapling_Id)
	{
		if (random->nextInt(5) == 0)
		{
			f = new CherryTreeLarge(false);
		}
		else
		{
			f = new CherryTreeFeature(false);
		}
	}
	else
	{
		return;
	}

	level->setTileAndData(x, y, z, 0, 0, Tile::UPDATE_NONE);

	if (!f->place(level, random, x, y, z))
	{
		int data = level->getData(x, y, z);
		level->setTileAndData(x, y, z, id, data, Tile::UPDATE_NONE);
	}

	delete f;
}