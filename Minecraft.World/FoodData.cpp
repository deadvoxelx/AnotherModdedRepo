#include "stdafx.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.h"
#include "net.minecraft.world.damagesource.h"
#include "com.mojang.nbt.h"
#include "FoodConstants.h"
#include "FoodData.h"

FoodData::FoodData()
{
	exhaustionLevel = 0;
	fastRegenBudget = 0.0f;
	tickTimer = 0;

	foodLevel = FoodConstants::MAX_FOOD;
	lastFoodLevel = FoodConstants::MAX_FOOD;
	saturationLevel = FoodConstants::START_SATURATION;
}

void FoodData::eat(int food, float saturationModifier)
{
	foodLevel = min(food + foodLevel, FoodConstants::MAX_FOOD);
	saturationLevel = min(saturationLevel + (float) food * saturationModifier * 2.0f, (float)foodLevel);
	fastRegenBudget += saturationModifier;
}

void FoodData::eat(FoodItem *item)
{
	eat(item->getNutrition(), item->getSaturationModifier());
}

void FoodData::tick(shared_ptr<Player> player)
{
	int difficulty = player->level->difficulty;

	lastFoodLevel = foodLevel;

	if (exhaustionLevel > FoodConstants::EXHAUSTION_DROP)
	{
		exhaustionLevel -= FoodConstants::EXHAUSTION_DROP;

		if (saturationLevel > 0)
		{
			saturationLevel = max(saturationLevel - 1, 0.0f);
		}
		else if (difficulty > Difficulty::PEACEFUL)
		{
			foodLevel = max(foodLevel - 1, 0);
		}
	}

	if (player->isHurt())
	{
		tickTimer++;

		if (fastRegenBudget > 0.0001f)
		{
			if (tickTimer >= FoodConstants::HEALTH_TICK_COUNT)
			{
				float oldHealth = player->getHealth();
				float requestedHeal = min(1.0f, fastRegenBudget * 10.0f);
				player->heal(requestedHeal);

				float healed = player->getHealth() - oldHealth;
				fastRegenBudget = max(fastRegenBudget - healed * 0.1f, 0.0f);
				if (fastRegenBudget < 0.0001f) fastRegenBudget = 0.0f;
				tickTimer = 0;
			}
		}
		else if (tickTimer >= FoodConstants::BASE_HEALTH_TICK_COUNT)
		{
			player->heal(1.0f);
			tickTimer = 0;
		}

		addExhaustion(FoodConstants::EXHAUSTION_HEAL);
	}

	else if (foodLevel <= FoodConstants::STARVE_LEVEL)
	{
		tickTimer++;
		if (tickTimer >= FoodConstants::HEALTH_TICK_COUNT)
		{
			if (player->getHealth() > 1 && difficulty >= Difficulty::HARD)
			{
				player->hurt(DamageSource::starve, 1);
			}
			tickTimer = 0;
		}
	}
	else
	{
		tickTimer = 0;
	}

}

void FoodData::readAdditionalSaveData(CompoundTag *entityTag)
{

	if (entityTag->contains(L"foodLevel"))
	{
		foodLevel = entityTag->getInt(L"foodLevel");
		tickTimer = entityTag->getInt(L"foodTickTimer");
		saturationLevel = entityTag->getFloat(L"foodSaturationLevel");
		exhaustionLevel = entityTag->getFloat(L"foodExhaustionLevel");
		fastRegenBudget = entityTag->contains(L"foodFastRegenBudget") ? entityTag->getFloat(L"foodFastRegenBudget") : 0.0f;
	}
}

void FoodData::addAdditonalSaveData(CompoundTag *entityTag)
{
	entityTag->putInt(L"foodLevel", foodLevel);
	entityTag->putInt(L"foodTickTimer", tickTimer);
	entityTag->putFloat(L"foodSaturationLevel", saturationLevel);
	entityTag->putFloat(L"foodExhaustionLevel", exhaustionLevel);
	entityTag->putFloat(L"foodFastRegenBudget", fastRegenBudget);
}

int FoodData::getFoodLevel()
{
	return foodLevel;
}

int FoodData::getLastFoodLevel()
{
	return lastFoodLevel;
}

bool FoodData::needsFood()
{
	return foodLevel < FoodConstants::MAX_FOOD;
}

void FoodData::addExhaustion(float amount)
{
	exhaustionLevel = min(exhaustionLevel + amount, FoodConstants::MAX_SATURATION * 2);
}

float FoodData::getExhaustionLevel()
{
	return exhaustionLevel;
}

float FoodData::getSaturationLevel()
{
	return saturationLevel;
}

void FoodData::setFoodLevel(int food)
{
	foodLevel = food;
}

void FoodData::setSaturation(float saturation)
{
	saturationLevel = saturation;
}

void FoodData::setExhaustion(float exhaustion)
{
	exhaustionLevel = exhaustion;
}
