#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"        
#include "Constants.hpp"
#include <iostream>


class Player : public Entity
{
private:
	//sf::Texture playertex;
	sf::Vector2f collPoints[8];
	void initPoints();
	bool active;
	// Movement variables
	sf::Vector2f pDirection;
	//Jump variables
	bool pWasSpacePressed;
	bool isSpacePressed;
	bool pIsJumping;
	bool gravity;
	bool showCollPoints;
	//Collision Variables
	bool topColliding;
	bool botColliding;
	bool rightColliding;
	bool leftColliding;

public:
	Player(sf::IntRect spriteintrect = sf::IntRect(), sf::Vector2f position = { 0,0 }, std::string texpath = PLAYER_SPRITE_IDLE);
	~Player();
	Player(const Player &origObj);
	Player & operator=(const Player &copyObj);

	void draw(sf::RenderTarget& window, sf::RenderStates state);
	sf::Vector2f GetPos()const;
	sf::Vector2f GetDirection()const;
	sf::FloatRect GetGlobalBounds() const;
	void Update(float dt);
	void SetDirection(float x, float y); //change direction
	void SetXDirection(float x);
	void SetYDirection(float y);
									//direction: 1 top 2 right 3 bottom 4 right
	void SetYPos(float x);
	void PrintCollPoints();
	void PrintPos();
	void NoColl();
	void Deactivate();
	void Reset();
	//Movement
	bool IsJumping()const;
	//Collision points
	sf::Vector2f GetCollPointPos(int i = 0)const;
	void UpdateCollisionPoints();
	void DrawCollPoints(sf::RenderTarget &win);
	void ShowCollPoints();
	void HideCollPoints();
	void SetCollDir(int direction); //returns 0 if no collision, 1 if y collision, 2 if x collision, 3 if both. 
	//Collision variables
	void SetTopColl(bool coll = true);
	void SetBotColl(bool coll = true);
	void SetRightColl(bool coll = true);
	void SetLeftColl(bool coll = true);
	bool CollBot()const;
	bool CollTop()const;
	bool CollLeft()const;
	bool CollRight()const;
};

#endif // !PLAYER_H
