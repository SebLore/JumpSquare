#include "Entity.hpp"

Entity::Entity()
{
	this->tex = sf::Texture();
	this->sprite = sf::Sprite();
	this->irect = sf::IntRect();
	this->texpath = "";
}

Entity::Entity(std::string texpath, sf::IntRect intrect, sf::Vector2f position)
{
	this->texpath = texpath;
	this->tex.loadFromFile(this->texpath, intrect);
	this->sprite.setTexture(this->tex);
	this->sprite.setPosition(position);
	this->irect = intrect;
}

Entity::Entity(const Entity & origObj)
{
	this->tex = origObj.tex;
	this->sprite = origObj.sprite;
	this->sprite.setTexture(tex);
	this->texpath = origObj.texpath;
	this->irect = origObj.irect;

}

Entity & Entity::operator=(const Entity & copyObj)
{
	if(this != &copyObj)
	{
		this->tex = copyObj.tex;
		this->sprite = copyObj.sprite;
		this->sprite.setTexture(this->tex);
		this->texpath = copyObj.texpath;
		this->irect = copyObj.irect;
	}
	return *this;
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	window.draw(this->sprite, states);
}


void Entity::Move(sf::Vector2f distance)
{
	sprite.move(distance);
}

void Entity::Move(float x, float y)
{
	sprite.move(sf::Vector2f{ x,y });
}

void Entity::SetIntRect(sf::IntRect newrect)
{
	sprite.setTextureRect(newrect);
	//sf::Texture temp;
	//temp.loadFromFile(this->texpath, newrect);
	//this->tex = temp;
	////this->tex.loadFromFile(texpath, this->irect);
	//this->sprite.setTexture(tex);
}

void Entity::SetPos(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}

void Entity::SetPos(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::SetScale(sf::Vector2f scale)
{
	sprite.setScale(scale);
}

void Entity::SetScale(float x, float y)
{
	sprite.setScale(x, y);
}

void Entity::SetTexture(std::string filepath, sf::IntRect rect)
{
	this->texpath = filepath;
	this->tex.loadFromFile(filepath, rect);
	this->sprite.setTexture(tex);
}

void Entity::SetTexture(sf::Texture texture)
{
	this->tex = texture;
}

void Entity::FlipSpriteH()
{
	//sprite.setOrigin(this->GetSpriteSize());
	this->sprite.scale(-1, 1);
	//sprite.setOrigin(0,0);
}

sf::Vector2f Entity::GetSpriteSize() const
{
	return {sprite.getTexture()->getSize().x * sprite.getScale().x,
			sprite.getTexture()->getSize().y * sprite.getScale().y,
			};
}

sf::Sprite Entity::GetSprite() const
{
	return sprite;
}

sf::Vector2f Entity::GetSpriteScale() const
{
	return this->sprite.getScale();
}

sf::Texture Entity::GetTexture() const
{
	return this->tex;
}


float Entity::GetX()const
{
	return sprite.getPosition().x;
}

float Entity::GetY()const
{
	return sprite.getPosition().y;
}

sf::Vector2f Entity::GetPosition() const
{
	return {this->GetX(), this->GetY()};
}

sf::FloatRect Entity::GetGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}
