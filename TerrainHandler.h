#ifndef TERRAINHANDLER_H
#define TERRAINHANDLER_H

#include "Terrain.h"

class TerrainHandler
{
private:
	Terrain * * terrain;
	uint cap;
	uint nrOfTerrain;
	bool existTerrain(sf::Vector2f position, sf::Vector2f size);
	void expand();
public:
	TerrainHandler(uint initcap = 10);
	~TerrainHandler();
	bool AddTerrain(sf::Vector2f position, sf::Vector2f size);
	void DrawTerrain(sf::RenderTarget &window);
};



#endif