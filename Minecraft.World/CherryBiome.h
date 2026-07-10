#pragma once
#include "Biome.h"

class CherryBiome : public Biome
{
public:
    CherryBiome(int id);

	virtual Feature *getTreeFeature(Random *random);
};
