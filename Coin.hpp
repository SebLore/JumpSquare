#ifndef COIN_HPP
#define COIN_HPP

#include "Entity.hpp"

class Coin : public Entity
{
private:
	bool active;
public:
	Coin(sf::IntRect intrect = sf::IntRect(), sf::Vector2f position = {0,0}, std::string texpath = COIN_SPRITE);
	~Coin();
	void PickedUp();
	bool IsActive();
	void Deactivate();
	void Activate();
	void Update(float dt);
};
#endif // !COIN_H
