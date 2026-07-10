#pragma once
#include "MobRenderer.h"

class Cow;

class CowRenderer : public MobRenderer
{
private:
	static ResourceLocation COW_LOCATION;
	static ResourceLocation COW_BLACK_LOCATION;
	static ResourceLocation COW_WHITE_LOCATION;
	static ResourceLocation COW_PINK_LOCATION;

public:
	CowRenderer(Model *model, float shadow);

	virtual void render(shared_ptr<Entity> _mob, double x, double y, double z, float rot, float a);
	virtual ResourceLocation *getTextureLocation(shared_ptr<Entity> mob);
};
