#include "EnemyHandler.h"

void EnemyHandler::expand()
{
	this->cap += 5;
	Enemy ** temp = new Enemy*[this->cap];
	for (uint i = 0; i < this->cap; i++)
	{
		if (i < this->amount)
			temp[i] = this->enemies[i];
		else
			temp[i] = nullptr;
	}
	delete[] enemies;
	this->enemies = temp;

}

EnemyHandler::EnemyHandler(uint initcap)
{
	this->amount = 0;
	this->cap = initcap;
	this->enemies = new Enemy*[initcap];
	for (uint i = 0; i < initcap; i++)
		enemies[i] = nullptr;
}

EnemyHandler::~EnemyHandler()
{
	if (amount > 0)
	{
		for (uint i = 0; i < this->amount; i++)
			delete this->enemies[i];
	}
	delete[] enemies;
}

void EnemyHandler::AddEnemy(sf::Vector2f position, sf::Vector2f size)
{
	if (this->amount >= this->cap)
		this->expand();
	this->enemies[this->amount] = new Enemy(position, size);
	this->amount++;
}

void EnemyHandler::DrawAll(sf::RenderTarget & window)
{
	for (uint i = 0; i < this->amount; i++) 
	{
		if(enemies[i]->IsActive() == true)
		enemies[i]->DrawTo(window);
	}
}

void EnemyHandler::Deactivate(int i)
{
	enemies[i]->Deactivate();
}

bool EnemyHandler::IsActive(int i)
{
	return enemies[i]->IsActive();
}

sf::FloatRect EnemyHandler::GetGlobalBounds(int i) const
{
	return enemies[i]->GetGlobalBounds();
}

uint EnemyHandler::GetNrOfEnemies() const
{
	return this->amount;
}

sf::Vector2f EnemyHandler::GetPosition(uint i) const
{
	return enemies[i]->GetPosition();
}
