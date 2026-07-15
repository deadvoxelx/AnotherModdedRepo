#pragma once
#include "Tile.h"

class Random;

class NetherrackTile : public Tile
{
public:
	static const int TYPE_DEFAULT = 0;
	static const int TYPE_SMOOTH = 1;

	static const int NETHERRACK_NAMES_LENGTH = 2;

	static const unsigned int NETHERRACK_NAMES[NETHERRACK_NAMES_LENGTH];
	static const wstring TEXTURE_NAMES[];

private:
	Icon** icons;

public:
	NetherrackTile(int id);
	virtual Icon* getTexture(int face, int data);
	virtual int getSpawnResourcesAuxValue(int data);
	void registerIcons(IconRegister* iconRegister);
};
