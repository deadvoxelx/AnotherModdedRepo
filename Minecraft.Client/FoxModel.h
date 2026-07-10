#pragma once
#include "Model.h"
#include "../Minecraft.World/Mob.h"

class FoxModel : public Model
{
public:
	ModelPart *head, *body, *leg0, *leg1, *leg2, *leg3;
    ModelPart *tail;
    ModelPart *upperBody;
private:
	static const int legSize = 8;
public:
	FoxModel();
    virtual void render(shared_ptr<Entity> entity, float time, float r, float bob, float yRot, float xRot, float scale, bool usecompiled);
    void prepareMobModel(shared_ptr<LivingEntity> mob, float time, float r, float a);
    virtual void setupAnim(float time, float r, float bob, float yRot, float xRot, float scale, shared_ptr<Entity> entity, unsigned int uiBitmaskOverrideAnim=0);
};