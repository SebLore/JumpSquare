#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Enemy : public Entity
{
private:
	float walkCycle;
	bool active = true;
public:
	Enemy(sf::Vector2f position = { 0, 0 }, sf::Vector2f size = { 40, 40 }, sf::Color eColor = { 255, 127, 0 });
	~Enemy();
	void Update(float dt);
	sf::FloatRect GetGlobalBounds()const;
	void Deactivate();
	bool IsActive();
};

#endif // !ENEMY_H
