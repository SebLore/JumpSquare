#include "TerrainHandler.h"

bool TerrainHandler::existTerrain(sf::Vector2f position, sf::Vector2f size)
{
	bool exists = false;

	for (uint i = 0; i < this->nrOfTerrain && (exists = false); i++)
		if (terrain[i]->GetPos() == position && terrain[i]->GetSize() == size)
			exists = true;

	return exists;
}

void TerrainHandler::expand()
{
	this->cap += 5;
	Terrain ** temp = new Terrain*[this->cap];
	for (uint i= 0; i < this->cap; i++)
	{
		if (i < this->nrOfTerrain)
			temp[i] = this->terrain[i];
		else
			temp[i] = nullptr;
	}
	this->terrain = temp;
}

TerrainHandler::TerrainHandler(uint initcap)
{
	this->cap = initcap;
	this->nrOfTerrain = 0;
	this->terrain = new Terrain*[initcap];
	for (uint i = 0; i < initcap; i++)
		this->terrain[i] = nullptr;
}

TerrainHandler::~TerrainHandler()
{
	if (this->nrOfTerrain > 0)
	{
		for (uint i = 0; i < this->cap; i++)
			delete terrain[i];
		delete[] terrain;
	}
}

bool TerrainHandler::AddTerrain(sf::Vector2f position, sf::Vector2f size)
{
	bool added = false;

	if (!this->existTerrain(position, size))
	{
		if (this->nrOfTerrain == this->cap)
			this->expand();
		this->terrain[this->nrOfTerrain] = new Terrain(position, size);
		this->nrOfTerrain++;
		added = true;
	}

	return added;
}

void TerrainHandler::DrawTerrain(sf::RenderTarget &window)
{
	for (uint i = 0; i < this->nrOfTerrain; i++)
		terrain[i]->DrawTo(window);
}
