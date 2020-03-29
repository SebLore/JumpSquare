#ifndef ENTITY_HPP
#define ENTITY_HPP

#include<SFML/Graphics.hpp>
#include "Constants.hpp"

class Entity : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture tex;
	sf::IntRect irect;
	std::string texpath;
public:
	//Constructors and operators
	virtual ~Entity();
	Entity();
	Entity(std::string texpath, sf::IntRect intrect = sf::IntRect(), sf::Vector2f position = WINDOW_CENTER);
	Entity(const Entity &origObj);
	Entity & operator=(const Entity &copyObj);
	//Functions
	virtual void Update(float dt) = 0; //Every Entity-derived class should handle updates differently, so we can remove this.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Move(sf::Vector2f distance);
	virtual void Move(float x, float y);
	virtual void SetIntRect(sf::IntRect newrect);
	virtual void SetPos(sf::Vector2f position);
	virtual void SetPos(float x, float y);
	virtual void SetScale(sf::Vector2f scale);
	virtual void SetScale(float x, float y);
	virtual void SetTexture(std::string filepath, sf::IntRect rec);
	virtual void SetTexture(sf::Texture texture);
	virtual void FlipSpriteH();
	virtual sf::Vector2f GetSpriteSize()const;
	virtual sf::Sprite GetSprite()const;
	virtual sf::Vector2f GetSpriteScale()const;
	virtual sf::Texture GetTexture()const;
	virtual float GetX()const;
	virtual float GetY()const;
	virtual sf::Vector2f GetPosition()const;
	virtual sf::FloatRect GetGlobalBounds() const;
	
};

#endif