#include "stdafx.h"
#include "OreTile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"

OreTile::OreTile(int id) : Tile(id, Material::stone)
{
}

int OreTile::getResource(int data, Random *random, int playerBonusLevel)
{
    if (id == Tile::coalOre_Id) return Item::coal_Id;
    if (id == Tile::diamondOre_Id) return Item::diamond_Id;
    if (id == Tile::lapisOre_Id) return Item::dye_powder_Id;
	if (id == Tile::emeraldOre_Id) return Item::emerald_Id;
	if (id == Tile::netherQuartz_Id) return Item::netherQuartz_Id;
	if (id == Tile::netherCoalOre_Id) return Item::netherCoal_Id;
	if (id == Tile::limestoneCoal_Id) return Item::coal_Id;
    if (id == Tile::limestoneDiamond_Id) return Item::diamond_Id;
    if (id == Tile::limestoneLapis_Id) return Item::dye_powder_Id;
    if (id == Tile::limestoneRedstone_Id) return Item::redStone_Id;
	if (id == Tile::graniteCoal_Id) return Item::coal_Id;
    if (id == Tile::graniteDiamond_Id) return Item::diamond_Id;
    if (id == Tile::graniteLapis_Id) return Item::dye_powder_Id;
    if (id == Tile::graniteRedstone_Id) return Item::redStone_Id;
    return id;
}

int OreTile::getResourceCount(Random *random)
{
    if (id == Tile::lapisOre_Id) return 4 + random->nextInt(5);
	if (id == Tile::limestoneRedstone_Id) return 4 + random->nextInt(5);
	if (id == Tile::graniteRedstone_Id) return 4 + random->nextInt(5);
    return 1;
}

int OreTile::getResourceCountForLootBonus(int bonusLevel, Random *random)
{
	if (bonusLevel > 0 && id != getResource(0, random, bonusLevel))
	{
		int bonus = random->nextInt(bonusLevel + 2) - 1;
		if (bonus < 0)
		{
			bonus = 0;
		}
		return getResourceCount(random) * (bonus + 1);
	}
	return getResourceCount(random);
}

void OreTile::spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel)
{
	Tile::spawnResources(level, x, y, z, data, odds, playerBonusLevel);

	// also spawn experience if the block is broken
	if (getResource(data, level->random, playerBonusLevel) != id)
	{
		int magicCount = 0;
		if (id == Tile::coalOre_Id || id == Tile::netherCoalOre_Id || id == Tile::limestoneCoal_Id || id == Tile::graniteCoal_Id)
		{
			magicCount = Mth::nextInt(level->random, 0, 2);
		}
		else if (id == Tile::diamondOre_Id || id == Tile::emeraldOre_Id || id == Tile::limestoneDiamond_Id || id == Tile::graniteDiamond_Id || id == Tile::limestoneRedstone_Id || id == Tile::graniteRedstone_Id)
		{
			magicCount = Mth::nextInt(level->random, 3, 7);
		}
		else if (id == Tile::lapisOre_Id || id == Tile::netherQuartz_Id || id == Tile::limestoneLapis_Id || id == Tile::graniteLapis_Id)
		{
			magicCount = Mth::nextInt(level->random, 2, 5);
		}
		popExperience(level, x, y, z, magicCount);
	}
}

int OreTile::getSpawnResourcesAuxValue(int data)
{
    // lapis spawns blue dye
    if (id == Tile::lapisOre_Id) return DyePowderItem::BLUE;
    return 0;
}
