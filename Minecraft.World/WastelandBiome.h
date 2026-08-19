#pragma once

#include "Biome.h"

class WastelandBiome : public Biome
{
public:
	WastelandBiome(int id);
	virtual void decorate(Level *level, Random *random, int xo, int zo);
};