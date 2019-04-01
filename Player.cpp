#include "Player.h"

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor):
Entity(position, size)
{
	this->startingPos = position;
	this->SetPos(position);
	this->SetFillColor(fillColor);
	this->initPoints();
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (this->active == true)
	{	
		sf::Vector2f movement = { 0.0f, 0.0f };
		//Movement
		if (pDirection.x <= 0.0f)
			rightCollision = false;
		if (pDirection.x >= 0.0f)
			leftCollision = false;

		//Rightward movement
		if (rightCollision == false) //Make sure we're not already colliding with smth.
		{
			//Check to see if input is being provided for moving right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//Check to see if the sprint key is enabled
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					if (pDirection.x < P_VERT_MAX_SPD)
						pDirection.x += 3.0f * dt;
					else
						pDirection.x = P_VERT_MAX_SPD;
				}
				//If we're not sprinting we move at 75% speed
				else
				{
					if (pDirection.x < P_VERT_MAX_SPD*0.75f)
						pDirection.x += 2.25f * dt;
					else
						pDirection.x = P_VERT_MAX_SPD*0.75;
				}
	
			}
			//Break momentum
			else if (pDirection.x > 0.0f)
			{
				pDirection.x -= 6.0f * dt;
				if (pDirection.x < 0.0f)
					pDirection.x = 0.0f;
			}
		}

		//Leftward movement
		if (leftCollision == false) //Make sure we're not already colliding with smth.
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					if (pDirection.x > -P_VERT_MAX_SPD)
						pDirection.x -= 3.0f * dt;
					else
						pDirection.x = -P_VERT_MAX_SPD;
				}
				else 
				{
				if (pDirection.x > -P_VERT_MAX_SPD*0.75)
					pDirection.x -= 2.25 * dt;
				else
					pDirection.x = -P_VERT_MAX_SPD*0.75;
				}
			}
			//Break momentum
			else if (pDirection.x < 0.0f)
			{
				pDirection.x += 6.0f * dt;
				if (pDirection.x > 0.0f)
					pDirection.x = 0.0f;
			}
		}

		//Jumping
		this->isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		if (this->isSpacePressed == true && pIsJumping == false && bottomCollision == true)
		{
			//If space was pressed, jump is started
			pIsJumping = true;
			pDirection.y = -pJumpSpeed; //Negative because in SFML the x and y axises go from top left to bottom right, 
			bottomCollision = false;    //hence to jump "up" we need a negative direction
		}

		if(bottomCollision == false || (bottomCollision == true && pIsJumping == true))
		{
		//Apply gravity to jump
			if (pDirection.y <= 0.0f)
				pDirection.y += (gGravity * dt);
			else if (pDirection.y > 0.0f && bottomCollision == false)
				pDirection.y += (1.68f * gGravity * dt);
		}
		if (bottomCollision == true)
			pIsJumping = false;
		movement = (pDirection * pSpeed *  dt);
		this->Move(movement);

		if (movement != sf::Vector2f(0.0f, 0.0f))
			this->UpdateCollisionPoints();

		pWasSpacePressed = isSpacePressed;
	}

}

void Player::UpdateCollisionPoints()
{
	sf::Vector2f playerPos = this->GetPosition();
	//top
	collPoints[0] = playerPos + topLeftColl;
	//right
	collPoints[1] = playerPos + topRightColl;
	//bottom
	collPoints[2] = playerPos + botLeftColl;
	//left
	collPoints[3] = playerPos + botRightColl;

	collPoints[4] = playerPos + leftTopColl;
	//right
	collPoints[5] = playerPos + leftBotColl;
	//bottom
	collPoints[6] = playerPos + rightTopColl;
	//left
	collPoints[7] = playerPos + leftTopColl;
}

void Player::PrintCollPoints()
{
	for (int i = 0; i < 8; i++)
		std::cout << "cp" << i << ": " << " x: " << collPoints[i].x << " y: " << collPoints[i].y << std::endl;
	if (bottomCollision)
		std::cout << "bottom colliding!" << std::endl;
}

void Player::PrintPos()
{
	std::cout << "player: x: " << this->GetPosition().x << " y: " << this->GetPosition().y << std::endl;
}

void Player::NoColl()
{
	bool topCollision = false;
	bool bottomCollision = false;
	bool rightCollision = false;
	bool leftCollision = false;
}

void Player::Deactivate()
{
	this->active = false;
	SetFillColor(sf::Color{255, 0, 0});
}

void Player::SetDirection(float x, float y)
{
	this->pDirection.x = x;
	this->pDirection.y = y;
}

void Player::SetCollDir(int dir, int tf) //1 top 2 bottom 3 left 4 right
{

	switch (dir)
	{
	case 0:
		if(tf==0)
			this->topCollision = true;
		else
			this->topCollision = false;
	    this->Move({ 0.0f, -this->pDirection.y});
		this->pDirection.y = 0.0f;
		break;
	case 1:
		if (tf == 0)
			this->bottomCollision = true;
		else
			this->topCollision = false;
		this->Move({ 0.0f,-this->pDirection.y});
		this->pDirection.y = 0.0f;
		break;
	case 2:
		if (tf == 0)
			this->leftCollision = true;
		else
			this->topCollision = false;
		this->Move({-this->pDirection.x, 0.0f});
		this->pDirection.x = 0.0f;
		break;
	case 3: 
		if (tf == 0)
			this->rightCollision = true;
		else
			this->topCollision = false;
		this->Move({ -this->pDirection.x, 0.0f});
		this->pDirection.x = 0.0f;
		break;
	}
}

void Player::initPoints() // 0 top 1 bot 2 left 3 right
{
	this->UpdateCollisionPoints();
}

void Player::Reset()
{
	this->pSpeed = 180.0f;
	// Movement variables
	this->pDirection = { 0.0f, 0.0f };
	this->SetPos(startingPos);
	this->pWasSpacePressed = false;
	this->pIsJumping = false;
	this->gravityApplied = false;
	//Collision Variables
	this->NoColl();
	this->initPoints();
	this->SetFillColor(sf::Color{ 0, 255, 0 });
	this->active = true;
}

bool Player::CollBot() const
{
	return this->bottomCollision;
}

bool Player::CollTop() const
{
	return this->bottomCollision;
}

bool Player::CollLeft() const
{
	return this->leftCollision;
}

bool Player::CollRight() const
{
	return this->rightCollision;
}

sf::Vector2f Player::GetPos()const { return this->GetPosition(); }

sf::Vector2f Player::GetDirection() const { return this->pDirection; }

sf::Vector2f Player::GetCollPoint(int i)const{return this->collPoints[i];}

sf::FloatRect Player::GetGlobalBounds() const{ return Entity::GetGlobalBounds();}