#pragma once
#include "TransparentTile.h"

class Leaf2Tile : public TransparentTile
{
	friend class Tile;
public:
	static const int REQUIRED_WOOD_RANGE = 4;
    static const int UPDATE_LEAF_BIT = 8;
	static const int PERSISTENT_LEAF_BIT = 4;

	static const int CHERRY_LEAF = 0;
	static const int PALM_LEAF = 1;
	static const int CHERRY_LEAF3 = 2;
	static const int CHERRY_LEAF4 = 3;

	static const int LEAF_NAMES_LENGTH = 4;

	static const unsigned int LEAF_NAMES[LEAF_NAMES_LENGTH];
	static const wstring TEXTURE_NAMES[];

	int *checkBuffer;

private:
	Icon** icons;

protected:
	Leaf2Tile(int id);
	virtual ~Leaf2Tile();
	virtual shared_ptr<ItemInstance> getSilkTouchItemInstance(int data);

public:
	virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual int getResourceCountForLootBonus(int bonusLevel, Random *random);
	virtual int getResourceCount(Random *random);
	virtual void spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel);

	virtual Icon* getTexture(int face, int data);
	void registerIcons(IconRegister* iconRegister);
	virtual bool isSolidRender(bool isServerLevel = false);

	virtual void animateTick(Level *level, int x, int y, int z, Random *random);
	virtual void onRemove(Level *level, int x, int y, int z, int id, int data);
	virtual void tick(Level *level, int x, int y, int z, Random *random);

private:
	void die(Level *level, int x, int y, int z);
};