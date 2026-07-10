#pragma once

#include "Biome.h"

class BeachBiome : public Biome
{
public:
	BeachBiome(int id);

	void decorate(Level *level, Random *random, int xo, int zo);
};
