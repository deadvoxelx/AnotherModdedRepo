#include "stdafx.h"
#include "ChestModel.h"
#include "ModelPart.h"

ChestModel::ChestModel()
{
	bottom = ((new ModelPart(this, 0, 0)))->setTexSize(64, 64);
	bottom->addBox(0.0f, 0.0f, 0.0f, 16, 16, 16, 0.0f);
	bottom->x = 0;
	bottom->y = 0;
	bottom->z = 0;

	bottom->compile(1.0f/16.0f);
}

void ChestModel::render(bool usecompiled)
{
	bottom->render(1 / 16.0f, usecompiled);
}
