#include "stdafx.h"
#include "Leaf2Tile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.item.enchantment.h"
#include "net.minecraft.world.h"
#include "net.minecraft.stats.h"
#include "net.minecraft.h"
#include "..\Minecraft.Client\Minecraft.h"

const unsigned int Leaf2Tile::LEAF_NAMES[LEAF_NAMES_LENGTH] = {
	IDS_TILE_LEAVES_CHERRY,
	IDS_TILE_LEAVES_PALM,
	IDS_TILE_LEAVES_CHERRY,
	IDS_TILE_LEAVES_CHERRY,
};

const wstring Leaf2Tile::TEXTURE_NAMES[] = {
	L"cherryLeaves", L"palmLeaves", L"cherryLeaves", L"cherryLeaves"
};

Leaf2Tile::Leaf2Tile(int id) : TransparentTile(id, Material::leaves, true)
{
	icons = nullptr;
	checkBuffer = nullptr;
	setTicking(true);
}

Leaf2Tile::~Leaf2Tile()
{
	delete [] checkBuffer;
}

int Leaf2Tile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Item::stick->id;
}

int Leaf2Tile::getResourceCountForLootBonus(int bonusLevel, Random *random)
{
	return getResourceCount(random) + random->nextInt(bonusLevel + 1);
}

int Leaf2Tile::getResourceCount(Random *random)
{
	return 1 + random->nextInt(2);
}

shared_ptr<ItemInstance> Leaf2Tile::getSilkTouchItemInstance(int data)
{
	return shared_ptr<ItemInstance>(new ItemInstance(Tile::leaves2, 1, data));
}

void Leaf2Tile::spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel)
{
	int d = data;
	if (d == CHERRY_LEAF)
	{
		if (!level->isClientSide)
		{
			int chance = 5;

			chance = 5;
			if (playerBonusLevel > 0)
			{
				chance -= 1 << playerBonusLevel;
				if (chance < 2)
				{
					chance = 2;
				}
			}
			if (level->random->nextInt(chance) == 0)
			{
				popResource(level, x, y, z, std::make_shared<ItemInstance>(Tile::cherrySapling_Id, 1, 0));
			}

			chance = 5;
			if (playerBonusLevel > 0)
			{
				chance -= 1 << playerBonusLevel;
				if (chance < 2)
				{
					chance = 2;
				}
			}
			if (level->random->nextInt(chance) == 0)
			{
				popResource(level, x, y, z, std::make_shared<ItemInstance>(Item::stick_Id, 1, 0));
			}

			chance = 5;
			if (playerBonusLevel > 0)
			{
				chance -= 1 << playerBonusLevel;
				if (chance < 2)
				{
					chance = 2;
				}
			}
			if (level->random->nextInt(chance) == 0)
			{
				popResource(level, x, y, z, std::make_shared<ItemInstance>(Item::cherries_Id, 1, 0));
			}
		}
	}
	else if (d == PALM_LEAF)
	{
		if (!level->isClientSide)
		{
			int chance = 5;

			chance = 5;
			if (playerBonusLevel > 0)
			{
				chance -= 1 << playerBonusLevel;
				if (chance < 2)
				{
					chance = 2;
				}
			}
			if (level->random->nextInt(chance) == 0)
			{
				popResource(level, x, y, z, std::make_shared<ItemInstance>(Tile::palmSapling_Id, 1, 0));
			}

			chance = 5;
			if (playerBonusLevel > 0)
			{
				chance -= 1 << playerBonusLevel;
				if (chance < 2)
				{
					chance = 2;
				}
			}
			if (level->random->nextInt(chance) == 0)
			{
				popResource(level, x, y, z, std::make_shared<ItemInstance>(Item::stick_Id, 1, 0));
			}
		}
	}
}

Icon* Leaf2Tile::getTexture(int face, int data)
{
	if (data < 0 || data >= LEAF_NAMES_LENGTH)
	{
		data = 0;
	}
	return icons[data];
}

void Leaf2Tile::registerIcons(IconRegister* iconRegister)
{
	icons = new Icon * [LEAF_NAMES_LENGTH];

	for (int i = 0; i < LEAF_NAMES_LENGTH; i++)
	{
		icons[i] = iconRegister->registerIcon(TEXTURE_NAMES[i]);
	}
}

bool Leaf2Tile::isSolidRender(bool isServerLevel)
{
	if(isServerLevel) return true;
	return !allowSame;
}

void Leaf2Tile::animateTick(Level *level, int x, int y, int z, Random *random)
{
	if (level->isRainingAt(x, y + 1, z) && !level->isTopSolidBlocking(x, y - 1, z) && random->nextInt(15) == 1)
	{
		double xx = x + random->nextFloat();
		double yy = y - 0.05;
		double zz = z + random->nextFloat();

		level->addParticle(eParticleType_dripWater, xx, yy, zz, 0, 0, 0);
	}
}

void Leaf2Tile::onRemove(Level *level, int x, int y, int z, int id, int data)
{
	int r = 1;
	int r2 = r + 1;

	if (level->hasChunksAt(x - r2, y - r2, z - r2, x + r2, y + r2, z + r2))
	{
		for (int xo = -r; xo <= r; xo++)
			for (int yo = -r; yo <= r; yo++)
				for (int zo = -r; zo <= r; zo++)
				{
					int t = level->getTile(x + xo, y + yo, z + zo);
					if (t == Tile::leaves2_Id)
					{
						int currentData = level->getData(x + xo, y + yo, z + zo);
						level->setData(x + xo, y + yo, z + zo, currentData, Tile::UPDATE_NONE);
					}
				}
	}

}

void Leaf2Tile::tick(Level *level, int x, int y, int z, Random *random)
{
	if (level->isClientSide) return;

	int currentData = level->getData(x, y, z);
	if ((currentData & UPDATE_LEAF_BIT) != 0 && (currentData & PERSISTENT_LEAF_BIT) == 0)
	{
		int r = REQUIRED_WOOD_RANGE;
		int r2 = r + 1;

		int W = 32;
		int WW = W * W;
		int WO = W / 2;
		if (checkBuffer == nullptr)
		{
			checkBuffer = new int[W * W * W];
		}

		if (level->hasChunksAt(x - r2, y - r2, z - r2, x + r2, y + r2, z + r2))
		{
			for (int xo = -r; xo <= r; xo++)
				for (int zo = -r; zo <= r; zo++)
					for (int yo = -r; yo <= r; yo++)
					{
						int t = level->getTile(x + xo, y + yo, z + zo);
						if (t == Tile::treeTrunk_Id || t == Tile::cherryLog_Id || t == Tile::grass_Id || t == Tile::dirt_Id)
						{
							checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO)] = 0;
						}
						else if (t == Tile::leaves2_Id)
						{
							checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO)] = -2;
						}
						else
						{
							checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO)] = -1;
						}
					}
					for (int i = 1; i <= REQUIRED_WOOD_RANGE; i++)
					{
						for (int xo = -r; xo <= r; xo++)
							for (int yo = -r; yo <= r; yo++)
								for (int zo = -r; zo <= r; zo++)
								{
									if (checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO)] == i - 1)
									{
										if (checkBuffer[(xo + WO - 1) * WW + (yo + WO) * W + (zo + WO)] == -2)
										{
											checkBuffer[(xo + WO - 1) * WW + (yo + WO) * W + (zo + WO)] = i;
										}
										if (checkBuffer[(xo + WO + 1) * WW + (yo + WO) * W + (zo + WO)] == -2)
										{
											checkBuffer[(xo + WO + 1) * WW + (yo + WO) * W + (zo + WO)] = i;
										}
										if (checkBuffer[(xo + WO) * WW + (yo + WO - 1) * W + (zo + WO)] == -2)
										{
											checkBuffer[(xo + WO) * WW + (yo + WO - 1) * W + (zo + WO)] = i;
										}
										if (checkBuffer[(xo + WO) * WW + (yo + WO + 1) * W + (zo + WO)] == -2)
										{
											checkBuffer[(xo + WO) * WW + (yo + WO + 1) * W + (zo + WO)] = i;
										}
										if (checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO - 1)] == -2)
										{
											checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO - 1)] = i;
										}
										if (checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO + 1)] == -2)
										{
											checkBuffer[(xo + WO) * WW + (yo + WO) * W + (zo + WO + 1)] = i;
										}
									}
								}
					}
		}

		int mid = checkBuffer[(WO) * WW + (WO) * W + (WO)];
		if (mid >= 0)
		{
			level->setData(x, y, z, currentData, Tile::UPDATE_NONE);
		}
		else
		{
			die(level, x, y, z);
		}
	}
}

void Leaf2Tile::die(Level *level, int x, int y, int z)
{
	Tile::spawnResources(level, x, y, z, level->getData(x, y, z), 0);
	level->removeTile(x, y, z);
}