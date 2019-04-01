#include<SFML/Graphics.hpp>
#include "Constants.h"

#ifndef ENTITY_H
#define ENTITY_H

//typedef enum Entity_Type{ NA = 0, PLAYER = 1, ENEMY = 2 } Entity_Type;

class Entity
{
private:
	sf::RectangleShape entity;
public:
	//Constructors and operators
	Entity(sf::Vector2f position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, sf::Vector2f size = {PSPRITESIZE});
	virtual ~Entity();
	
	//Functions
	virtual void DrawTo(sf::RenderTarget &window);
	virtual void Move(sf::Vector2f distance);
	virtual void SetPos(sf::Vector2f position);
	virtual void SetSize(sf::Vector2f size);
	virtual void SetFillColor(sf::Color &color);
	virtual void Update(float dt) = 0;
	virtual uint GetNrOfPoints()const;
	virtual float GetX()const;
	virtual float GetY()const;
	virtual sf::Vector2f GetPosition()const;
	virtual sf::Vector2f GetPoint(uint index)const;
	virtual sf::FloatRect GetGlobalBounds() const;
	
};

#endif