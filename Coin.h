#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity
{
private:
	bool active;
public:
	Coin(sf::Vector2f position = {}, sf::Vector2f size = { 12, 24 }, sf::Color fillColor = { 255, 255, 0 });
	~Coin();
	void PickedUp();
	bool IsActive();
	void Update(float dt);
};
#endif // !COIN_H
