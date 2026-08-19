#pragma once
#include "Biome.h"

class RainforestBiome : public Biome
{
public:
	RainforestBiome(int id);
	Feature *getTreeFeature(Random *random);
	Feature *getGrassFeature(Random *random);
};
