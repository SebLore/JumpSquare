#include "Entity.h"        
#include "Constants.h"
#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Entity
{
private:
	sf::Vector2f collPoints[8];
	void initPoints();
	bool active  = true;
	float pSpeed = 180.0f;
	// Movement variables
	sf::Vector2f pDirection  = { 0.0f, 0.0f };
	sf::Vector2f startingPos = {100.0f, 100.0f};
	//Jump variables
	bool pWasSpacePressed = false;
	bool isSpacePressed   = false;
	bool pIsJumping		  = false;
	bool gravityApplied	  = false;
	//Collision Variables
	bool topCollision	  = false;
	bool bottomCollision  = false;
	bool rightCollision   = false;
	bool leftCollision    = false;

	
public:
	/*Player();*/
	Player(sf::Vector2f position = { 0, 0 }, sf::Vector2f size = { 40, 40 }, sf::Color pColor = { 0, 255, 0 });
	~Player();
	sf::Vector2f GetPos()const;
	sf::Vector2f GetDirection()const;
	sf::Vector2f GetCollPoint(int i = 0)const;
	sf::FloatRect GetGlobalBounds() const;
	void Update(float dt);
	void UpdateCollisionPoints();
	void SetDirection(float x, float y); //change direction
	void SetCollDir(int direction, int tf = 0/*0 sets to true, 1 sets to false*/); //1 top 2 bottom 3 left 4 right
	void PrintCollPoints();
	void PrintPos();
	void NoColl();
	void Deactivate();
	void Reset();
	bool CollBot()const;
	bool CollTop()const;
	bool CollLeft()const;
	bool CollRight()const;
};

#endif // !PLAYER_H
