#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, sf::Vector2f size, sf::Color eColor):
	Entity(position, size)
{
	this->SetPos(position);
	this->SetFillColor(eColor);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
}

sf::FloatRect Enemy::GetGlobalBounds() const
{
	return Entity::GetGlobalBounds();
}

void Enemy::Deactivate()
{
	this->active = false;
}

bool Enemy::IsActive()
{
	return this->active;
}
