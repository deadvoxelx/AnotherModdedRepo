#pragma once
#include "Tile.h"

class ChunkRebuildData;
class ColoredPlanksTile : public Tile
{
	friend class ChunkRebuildData;
public:
	static const int TYPE_WHITE = 0;
	static const int TYPE_SILVER = 1;
	static const int TYPE_GRAY = 2;
	static const int TYPE_BLACK = 3;
	static const int TYPE_BROWN = 4;
	static const int TYPE_RED = 5;
	static const int TYPE_ORANGE = 6;
	static const int TYPE_YELLOW = 7;
	static const int TYPE_LIME = 8;
	static const int TYPE_GREEN = 9;
	static const int TYPE_CYAN = 10;
	static const int TYPE_LIGHTBLUE = 11;
	static const int TYPE_BLUE = 12;
	static const int TYPE_PURPLE = 13;
	static const int TYPE_MAGENTA = 14;
	static const int TYPE_PINK = 15;

	static const wstring TEXTURE_NAMES[];

	static const int COLORED_PLANK_NAMES_LENGTH = 16;

	static const unsigned int COLORED_PLANK_NAMES[COLORED_PLANK_NAMES_LENGTH];

private:
	Icon **icons;

public:

    ColoredPlanksTile(int id);

public:
	virtual Icon *getTexture(int face, int data);

	virtual unsigned int getDescriptionId(int iData = -1);
	virtual int getSpawnResourcesAuxValue(int data);
	void registerIcons(IconRegister *iconRegister);
};