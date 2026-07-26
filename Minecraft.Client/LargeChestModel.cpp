#include "stdafx.h"
#include "LargeChestModel.h"
#include "ModelPart.h"

LargeChestModel::LargeChestModel()
{
	bottom = ((new ModelPart(this, 0, 0)))->setTexSize(128, 64);
	bottom->addBox(0.0f, 0.0f, 0.0f, 16+16, 16, 16, 0.0f);
	bottom->x = 0;
	bottom->y = 0;
	bottom->z = 0;

	bottom->compile(1.0f/16.0f);
}
