#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H
#include "Enemy.h"

class EnemyHandler
{
private:
	Enemy ** enemies;
	uint amount;
	uint cap;
	void expand();
public:
	EnemyHandler(uint initcap = 10);
	~EnemyHandler();
	void AddEnemy(sf::Vector2f position, sf::Vector2f size = {40, 40});
	void DrawAll(sf::RenderTarget &window);
	void Deactivate(int i);
	bool IsActive(int i);
	sf::FloatRect GetGlobalBounds(int i)const;
	uint GetNrOfEnemies()const;
	sf::Vector2f GetPosition(uint i)const;
};
#endif // !1
