#include "stdafx.h"
#include "CherryLogTile.h"
#include "net.minecraft.world.h"
#include "Facing.h"

CherryLogTile::CherryLogTile(int id) : Tile(id, Material::wood)
{
	iconTop = nullptr;
}

Icon *CherryLogTile::getTexture(int face, int data)
{
	if (face == Facing::UP || face == Facing::DOWN) return iconTop;
	return icon;
}

void CherryLogTile::registerIcons(IconRegister *iconRegister)
{
	icon = iconRegister->registerIcon(getIconName() + L"_side");
	iconTop = iconRegister->registerIcon(getIconName() + L"_top");
}