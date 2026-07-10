#pragma once
#include "Tile.h"

class ChunkRebuildData;
class CherryLogTile : public Tile
{
	friend class ChunkRebuildData;
private:
	Icon *iconTop;

public:
	CherryLogTile(int id);
public:
	virtual Icon *getTexture(int face, int data);
	void registerIcons(IconRegister *iconRegister);
};