#include "Coin.hpp"

Coin::Coin(sf::IntRect intrect, sf::Vector2f position, std::string texpath):
	Entity(texpath, intrect, position)
{
	this->active = true;
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

void Coin::Deactivate()
{
	this->active = false;
}

void Coin::Activate()
{
	this->active = true;
}

void Coin::Update(float dt)
{
}
