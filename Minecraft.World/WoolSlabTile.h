#pragma once
using namespace std;

#include "HalfSlabTile.h"

class ChunkRebuildData;

class WoolSlabTile : public HalfSlabTile
{
	friend ChunkRebuildData;
public:
	static const int WHITE = 0;
	static const int SILVER = 1;
	static const int GRAY = 2;
	static const int BLACK = 3;
	static const int BROWN = 4;
	static const int RED = 5;
	static const int ORANGE = 6;
	static const int YELLOW = 7;

	static const int SLAB_NAMES_LENGTH = 8;

	static const unsigned int SLAB_NAMES[SLAB_NAMES_LENGTH];

public:
	WoolSlabTile(int id, bool fullSize);

	virtual Icon *getTexture(int face, int data);

	void registerIcons(IconRegister *iconRegister);
	virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual unsigned int getDescriptionId(int iData = -1);
	virtual int getAuxName(int auxValue);
protected:
	virtual shared_ptr<ItemInstance> getSilkTouchItemInstance(int data);
};