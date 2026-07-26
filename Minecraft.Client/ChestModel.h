#pragma once

#include "Model.h"

class Cube;

class ChestModel : public Model
{
public:
	using Model::render;

	ModelPart *bottom;

	ChestModel();
	void render(bool usecompiled);
};
