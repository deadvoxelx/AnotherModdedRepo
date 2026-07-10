#include "stdafx.h"
#include "FoxRenderer.h"
#include "MultiPlayerLocalPlayer.h"
#include "../Minecraft.World/net.minecraft.world.entity.animal.h"

ResourceLocation *FoxRenderer::FOX_LOCATION = new ResourceLocation(TN_MOB_FOX);
ResourceLocation *FoxRenderer::FOX_TAME_LOCATION = new ResourceLocation(TN_MOB_FOX_TAME);
ResourceLocation *FoxRenderer::FOX_ANGRY_LOCATION = new ResourceLocation(TN_MOB_FOX_ANGRY);
ResourceLocation *FoxRenderer::FOX_COLLAR_LOCATION = new ResourceLocation(TN_MOB_WOLF_COLLAR);

FoxRenderer::FoxRenderer(Model *model, Model *armor, float shadow) : MobRenderer(model, shadow)
{
	setArmor(armor);
}

float FoxRenderer::getBob(shared_ptr<LivingEntity> _mob, float a)
{
	shared_ptr<Fox> mob = dynamic_pointer_cast<Fox>(_mob);

	return mob->getTailAngle();
}

int FoxRenderer::prepareArmor(shared_ptr<LivingEntity> mob, int layer, float a)
{
	if (mob->isInvisibleTo(Minecraft::GetInstance()->player)) return -1;

	shared_ptr<Fox> fox = dynamic_pointer_cast<Fox>(mob);
	if (layer == 0 && fox->isWet())
	{
		float brightness = fox->getBrightness(a) * fox->getWetShade(a);
		bindTexture(FOX_LOCATION);
		glColor3f(brightness, brightness, brightness);

		return 1;
	}
	if (layer == 1 && fox->isTame())
	{
		bindTexture(FOX_COLLAR_LOCATION);
		float brightness = SharedConstants::TEXTURE_LIGHTING ? 1 : fox->getBrightness(a);
		int color = fox->getCollarColor();
		glColor3f(brightness * Sheep::COLOR[color][0], brightness * Sheep::COLOR[color][1], brightness * Sheep::COLOR[color][2]);

		return 1;
	}
	return -1;
}

ResourceLocation *FoxRenderer::getTextureLocation(shared_ptr<Entity> _mob)
{
	shared_ptr<Fox> mob = dynamic_pointer_cast<Fox>(_mob);
	if (mob->isTame())
	{
		return FOX_TAME_LOCATION;
	}
	if (mob->isAngry())
	{
		return FOX_ANGRY_LOCATION;
	}
	return FOX_LOCATION;
}

void FoxRenderer::scale(shared_ptr<LivingEntity> _mob, float a)
{
	glScalef(0.75, 0.75, 0.75);
}