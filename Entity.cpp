#include "Entity.h"

Entity::Entity(sf::Vector2f position, sf::Vector2f size)
{
	this->entity.setPosition(position);
	this->entity.setSize(size);
}

Entity::~Entity()
{

}

void Entity::DrawTo(sf::RenderTarget & window)
{
	window.draw(entity);
}


void Entity::Move(sf::Vector2f distance)
{
	entity.move(distance);
}

void Entity::SetPos(sf::Vector2f newPos)
{
	entity.setPosition(newPos);
}

void Entity::SetSize(sf::Vector2f size)
{
	entity.setSize(size);
}

void Entity::SetFillColor(sf::Color &color)
{
	entity.setFillColor(color);
}

float Entity::GetX()const
{
	return entity.getPosition().x;
}

float Entity::GetY()const
{
	return entity.getPosition().y;
}

sf::Vector2f Entity::GetPosition() const
{
	return {this->GetX(), this->GetY()};
}

uint Entity::GetNrOfPoints() const
{
	return entity.getPointCount();
}

sf::Vector2f Entity::GetPoint(uint index) const
{
	return entity.getPoint(index);
}

sf::FloatRect Entity::GetGlobalBounds() const
{
	return this->entity.getGlobalBounds();
}
