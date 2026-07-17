#pragma once
#include "Tile.h"

class Random;

class BrickTile : public Tile
{
public:
	static const int TYPE_DEFAULT = 0;
	static const int TYPE_STONE = 1;
	static const int TYPE_LIMESTONE = 2;
	static const int TYPE_GRANITE = 3;

	static const int BRICK_NAMES_LENGTH = 4;

	static const unsigned int BRICK_NAMES[BRICK_NAMES_LENGTH];
	static const wstring TEXTURE_NAMES[];

private:
	Icon** icons;

public:
	BrickTile(int id);
	virtual Icon* getTexture(int face, int data);
	virtual int getSpawnResourcesAuxValue(int data);
	void registerIcons(IconRegister* iconRegister);
};