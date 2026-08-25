#include "stdafx.h"
#include "net.minecraft.world.level.tile.entity.h"
#include "net.minecraft.world.item.h"
#include "WeighedRandom.h"
#include "WeighedTreasure.h"

WeighedTreasure::WeighedTreasure(int itemId, int auxValue, int minCount, int maxCount, int weight) : WeighedRandomItem(weight)
{
	this->item = nullptr;
	this->itemId = itemId;
	this->auxValue = auxValue;
	this->minCount = minCount;
	this->maxCount = maxCount;
}

WeighedTreasure::WeighedTreasure(shared_ptr<ItemInstance> item, int minCount, int maxCount, int weight) : WeighedRandomItem(weight)
{
	this->item = item;
	this->itemId = -1;
	this->auxValue = 0;
	this->minCount = minCount;
	this->maxCount = maxCount;
}

shared_ptr<ItemInstance> WeighedTreasure::createItem() const
{
	if (item != nullptr) return item->copy();
	if (itemId < 0 || itemId >= Item::ITEM_NUM_COUNT || Item::items[itemId] == nullptr)
	{
		return nullptr;
	}
	return std::make_shared<ItemInstance>(itemId, 1, auxValue);
}

static bool addItemToEmptySlot(Random *random, shared_ptr<Container> dest, shared_ptr<ItemInstance> item)
{
	if (random == nullptr || dest == nullptr || item == nullptr || item->count <= 0) return false;
	unsigned int size = dest->getContainerSize();
	if (size == 0) return false;

	unsigned int start = random->nextInt(size);
	for (unsigned int offset = 0; offset < size; offset++)
	{
		unsigned int slot = (start + offset) % size;
		if (dest->getItem(slot) == nullptr)
		{
			dest->setItem(slot, item);
			return true;
		}
	}
	return false;
}

static void addTreasureToContainer(Random *random, shared_ptr<Container> dest, shared_ptr<ItemInstance> item, int count)
{
	if (item == nullptr || count <= 0) return;

	int maxStackSize = item->getMaxStackSize();
	if (maxStackSize >= count)
	{
		item->count = count;
		addItemToEmptySlot(random, dest, item);
		return;
	}

	while (count > 0)
	{
		shared_ptr<ItemInstance> copy = item->copy();
		copy->count = 1;
		if (!addItemToEmptySlot(random, dest, copy)) return;
		count--;
	}
}

void WeighedTreasure::addChestItems(Random *random, WeighedTreasureArray items, shared_ptr<Container> dest, int numRolls)
{
	for (int r = 0; r < numRolls; r++)
	{
		WeighedTreasure *treasure = static_cast<WeighedTreasure *>(WeighedRandom::getRandomItem(random, *((WeighedRandomItemArray *)&items)));
		if (treasure == nullptr) continue;

		shared_ptr<ItemInstance> item = treasure->createItem();
		if (item == nullptr) continue;
		int count = treasure->minCount + random->nextInt(treasure->maxCount - treasure->minCount + 1);
		addTreasureToContainer(random, dest, item, count);
	}
}

void WeighedTreasure::addDispenserItems(Random *random, WeighedTreasureArray items, shared_ptr<DispenserTileEntity> dest, int numRolls)
{
	for (int r = 0; r < numRolls; r++)
	{
		WeighedTreasure *treasure = static_cast<WeighedTreasure *>(WeighedRandom::getRandomItem(random, *((WeighedRandomItemArray *)&items)));
		if (treasure == nullptr) continue;

		shared_ptr<ItemInstance> item = treasure->createItem();
		if (item == nullptr) continue;
		int count = treasure->minCount + random->nextInt(treasure->maxCount - treasure->minCount + 1);
		addTreasureToContainer(random, dest, item, count);
	}
}

WeighedTreasureArray WeighedTreasure::addToTreasure(WeighedTreasureArray items, WeighedTreasure *extra)
{
	WeighedTreasureArray result(items.length + 1);
	int i = 0;

	for (int j = 0; j < items.length; j++)
	{
		result[i++] = items[j];
	}

	result[i++] = extra;

	return result;
}
