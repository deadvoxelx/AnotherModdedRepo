#pragma once
#include "MobRenderer.h"

class FoxRenderer : public MobRenderer
{
private:
	static ResourceLocation *FOX_LOCATION;
	static ResourceLocation *FOX_TAME_LOCATION;
	static ResourceLocation *FOX_ANGRY_LOCATION;
	static ResourceLocation *FOX_COLLAR_LOCATION;

public:
	FoxRenderer(Model *model, Model *armor, float shadow);

protected:
	virtual float getBob(shared_ptr<LivingEntity> _mob, float a);
	virtual int prepareArmor(shared_ptr<LivingEntity> mob, int layer, float a);
	virtual ResourceLocation *getTextureLocation(shared_ptr<Entity> mob);
    virtual void scale(shared_ptr<LivingEntity> mob, float a);
};