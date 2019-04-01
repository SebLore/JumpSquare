#include "Coin.h"

Coin::Coin(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor):
	Entity(position, size)
{
	this->active = true;
	this->SetFillColor(fillColor);
	this->SetPos(position);
}

Coin::~Coin()
{
}

void Coin::PickedUp()
{
	if(this->active == true) 
		this->active = false;
}

bool Coin::IsActive()
{
	return this->active;
}

void Coin::Update(float dt)
{
}
