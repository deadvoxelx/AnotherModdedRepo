#pragma once
#include "Feature.h"

class CherryTreeFeature : public Feature
{
private:
	const int baseHeight;

public:
	CherryTreeFeature(bool doUpdate);
	CherryTreeFeature(bool doUpdate, int baseHeight);

	virtual bool place(Level *level, Random *random, int x, int y, int z);
};