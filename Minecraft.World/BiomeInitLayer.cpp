#include "stdafx.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.level.newbiome.layer.h"
#include "net.minecraft.world.level.h"
#include "BiomeInitLayer.h"

BiomeInitLayer::BiomeInitLayer(int64_t seed, shared_ptr<Layer>parent, LevelType *levelType) : Layer(seed)
{
	this->parent = parent;

	startBiomes = BiomeArray(10);
	startBiomes[0] = Biome::plains;
	startBiomes[1] = Biome::forest;
	startBiomes[2] = Biome::desert;
	startBiomes[3] = Biome::extremeHills;
	startBiomes[4] = Biome::swampland;
	startBiomes[5] = Biome::jungle;
	startBiomes[6] = Biome::cherryForest;
	startBiomes[7] = Biome::birchForest;
	startBiomes[8] = Biome::wasteland;
	startBiomes[9] = Biome::rainForest;
}

BiomeInitLayer::~BiomeInitLayer()
{
	delete [] startBiomes.data;
}

intArray BiomeInitLayer::getArea(int xo, int yo, int w, int h)
{
	intArray b = parent->getArea(xo - 1, yo - 1, w + 2, h + 2);
	int bw = w + 2;

	intArray result = IntCache::allocate(w * h);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			initRandom(x + xo, y + yo);
            int old = b[(x + 1) + (y + 1) * bw];
            if (old == 0)
			{
                result[x + y * w] = 0;
            }
			else if (old == Biome::mushroomIsland->id)
			{
                result[x + y * w] = old;
            }
			else if (old == 1)
			{
                Biome *pickedBiome = startBiomes[nextRandom(startBiomes.length)];
                if (pickedBiome == Biome::cherryForest && nextRandom(5) != 0)
                {
                    pickedBiome = Biome::plains;
                }
                if ((pickedBiome == Biome::birchForest || pickedBiome == Biome::rainForest) && nextRandom(3) != 0)
                {
                    pickedBiome = Biome::forest;
                }
                if (pickedBiome == Biome::wasteland && nextRandom(3) != 0)
                {
                    pickedBiome = Biome::desert;
                }
                if (pickedBiome == Biome::desert || pickedBiome == Biome::wasteland)
                {
                    int _n = b[(x + 1) + (y + 0) * bw];
                    int _e = b[(x + 2) + (y + 1) * bw];
                    int _w = b[(x + 0) + (y + 1) * bw];
                    int _s = b[(x + 1) + (y + 2) * bw];
                    if (_n == Biome::iceFlats->id || _n == Biome::iceMountains->id || _n == Biome::frozenOcean->id || _n == Biome::frozenRiver->id || _n == Biome::taiga->id || _n == Biome::taigaHills->id ||
                        _e == Biome::iceFlats->id || _e == Biome::iceMountains->id || _e == Biome::frozenOcean->id || _e == Biome::frozenRiver->id || _e == Biome::taiga->id || _e == Biome::taigaHills->id ||
                        _w == Biome::iceFlats->id || _w == Biome::iceMountains->id || _w == Biome::frozenOcean->id || _w == Biome::frozenRiver->id || _w == Biome::taiga->id || _w == Biome::taigaHills->id ||
                        _s == Biome::iceFlats->id || _s == Biome::iceMountains->id || _s == Biome::frozenOcean->id || _s == Biome::frozenRiver->id || _s == Biome::taiga->id || _s == Biome::taigaHills->id)
                    {
                        pickedBiome = (nextRandom(2) == 0) ? Biome::plains : Biome::forest;
                    }
                }
                result[x + y * w] = pickedBiome->id;
            }
			else
			{
				result[x + y * w] = (nextRandom(3) == 0) ? Biome::taiga->id : Biome::iceFlats->id;
			}
		}
	}

	return result;
}
