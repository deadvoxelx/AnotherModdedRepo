#pragma once
using namespace std;

#include "HalfSlabTile.h"

class ChunkRebuildData;

class WoolSlab2Tile : public HalfSlabTile
{
	friend ChunkRebuildData;
public:
	static const int LIME = 0;
	static const int GREEN = 1;
	static const int CYAN = 2;
	static const int LIGHT_BLUE = 3;
	static const int BLUE = 4;
	static const int PURPLE = 5;
	static const int MAGENTA = 6;
	static const int PINK = 7;

	static const int SLAB_NAMES_LENGTH = 8;

	static const unsigned int SLAB_NAMES[SLAB_NAMES_LENGTH];

public:
	WoolSlab2Tile(int id, bool fullSize);

	virtual Icon *getTexture(int face, int data);

	void registerIcons(IconRegister *iconRegister);
	virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual unsigned int getDescriptionId(int iData = -1);
	virtual int getAuxName(int auxValue);
protected:
	virtual shared_ptr<ItemInstance> getSilkTouchItemInstance(int data);
};