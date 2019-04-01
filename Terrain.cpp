#include "Terrain.h"
#include "Terrain.h"

Terrain::Terrain(sf::Vector2f position, sf::Vector2f size)
{
	this->terrain.setPosition(position);
	this->terrain.setSize(size);
	this->isEnabled = true;
}

Terrain::~Terrain()
{
}

Terrain::Terrain(const Terrain & origObj)
{
	this->terrain	= origObj.terrain;
	this->isEnabled	= origObj.isEnabled;
}

Terrain & Terrain::operator=(const Terrain & copyObj)
{
	if(this != &copyObj)
	{ 
		this->terrain	= copyObj.terrain;
		this->isEnabled = copyObj.isEnabled;
	}
	return *this;
}

bool & Terrain::operator==(const Terrain & compObj) const
{
	return (this->terrain == compObj.terrain);
}

bool & Terrain::operator!=(const Terrain & compObj) const
{
	return !(this->terrain == combObj.terrain);
}

void Terrain::DrawTo(sf::RenderTarget & window)
{
	if(this->isEnabled == true)
		window.draw(terrain);
}

void Terrain::Enable()
{
	this->isEnabled = true;
}

void Terrain::Disable()
{
	this->isEnabled = false;
}

float Terrain::GetX() const
{
	return terrain.getPosition().x;
}

float Terrain::GetY() const
{
	return terrain.getPosition().y;
}

sf::Vector2f Terrain::GetPos() const
{
	return terrain.getPosition();
}

sf::Vector2f Terrain::GetSize() const
{
	return this->terrain.getSize();
}

sf::FloatRect Terrain::GetGlobalBounds() const
{
	return this->terrain.getGlobalBounds();
}
