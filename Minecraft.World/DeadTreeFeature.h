#pragma once
#include "Feature.h"

class DeadTreeFeature : public Feature
{
public:
	DeadTreeFeature(bool doUpdate);

	virtual bool place(Level *level, Random *random, int x, int y, int z);
};