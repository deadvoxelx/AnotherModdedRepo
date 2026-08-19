#pragma once
#include "Biome.h"

class BirchBiome : public Biome
{
public:
    BirchBiome(int id);

	virtual Feature *getTreeFeature(Random *random);
};
