#include "Player.hpp"

Player::Player(sf::IntRect spriteintrect, sf::Vector2f position, std::string texpath):
	Entity(texpath, spriteintrect, position)
{
	this->pDirection = { 0.0f, 0.0f };
	this->active = true;
	this->showCollPoints	= true;
	this->pWasSpacePressed  = false;
	this->isSpacePressed	= false;
	this->pIsJumping		= false;
	this->topColliding		= false;
	this->botColliding		= false;
	this->rightColliding	= false;
	this->leftColliding		= false;
	this->initPoints();
}

Player::~Player()
{
}

Player::Player(const Player & origObj):
	Entity(origObj)
{
	// Movement variables
	this->pDirection		= origObj.pDirection;
	//Jump variables

	this->pWasSpacePressed  = origObj.pWasSpacePressed;
	this->isSpacePressed	= origObj.isSpacePressed;
	this->pIsJumping		= origObj.pIsJumping;
	this->gravity			= origObj.gravity;
	//Collision Variables
	this->showCollPoints    = origObj.showCollPoints;
	this->topColliding		= origObj.topColliding;
	this->botColliding	= origObj.botColliding;
	this->rightColliding	= origObj.rightColliding;
	this->leftColliding		= origObj.leftColliding;
}

Player & Player::operator=(const Player & copyObj)
{
	if (this != &copyObj)
	{
		Entity::operator=(copyObj);
		this->pDirection		= copyObj.pDirection;
		this->showCollPoints    = copyObj.showCollPoints;
		this->active			= copyObj.active;
		this->pWasSpacePressed	= copyObj.pWasSpacePressed;
		this->isSpacePressed	= copyObj.isSpacePressed;
		this->pIsJumping		= copyObj.pIsJumping;
		this->topColliding		= copyObj.topColliding;
		this->botColliding	= copyObj.botColliding;
		this->rightColliding	= copyObj.rightColliding;
		this->leftColliding		= copyObj.leftColliding;
	}
	return *this;
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates state)
{
	Entity::draw(window, state);

	//if (showCollPoints == true)
	//{
		sf::CircleShape drawCollPoint;
		drawCollPoint.setFillColor(sf::Color::Red);
		drawCollPoint.setRadius(4.0f);
		drawCollPoint.setOrigin(4.0f, 4.0f);
		for (uint i = 0; i < 8; i++) {
			drawCollPoint.setPosition(collPoints[i]);
			drawCollPoint.setOrigin({ this->collPoints[i].x, this->collPoints[i].y });
			window.draw(drawCollPoint, state);
		}
	//}
	/*sf::CircleShape point;
	point.setFillColor(sf::Color::Red);
	point.setRadius(4.0f);
	point.setOrigin(4.0f, 4.0f);
	for (uint i = 0; i < 8; i++)
	{
		point.setPosition(this->collPoints[i]);
	    point.setOrigin({ this->collPoints[i].x, this->collPoints[i].y });
		win.draw(point);
	*/
}

void Player::Update(float dt)
{
	if (this->active == true)//Only update if the player character is enabled
	{
	//	sf::Vector2f movement = { 0.0f, 0.0f };
		//Movement
		if (pDirection.x <= 0.0f)
			rightColliding = false;
		if (pDirection.x >= 0.0f)
			leftColliding = false;

		////Rightward movement
		if (rightColliding == false) //Make sure we're not already colliding with smth.
		{
			//Check to see if input is being provided for moving right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (GetSpriteScale().x < 0)
					FlipSpriteH();
				//Check to see if the sprint key is enabled
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					if (pDirection.x < P_V_MAX_SPD)
						pDirection.x += 3.0f * dt;
					else
						pDirection.x = P_V_MAX_SPD;
					
				}
				//If we're not sprinting we move at 75% speed
				else
				{
					if (pDirection.x < P_V_MAX_SPD*0.75f)
						pDirection.x += 2.25f * dt;
					else
						pDirection.x = P_V_MAX_SPD * 0.75;
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
		if (leftColliding == false) //Make sure we're not already colliding with smth.
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
			{
				if (GetSpriteScale().x > 0)
					FlipSpriteH();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					if (pDirection.x > -P_V_MAX_SPD)
						pDirection.x -= 3.0f * dt;
					else
						pDirection.x = -P_V_MAX_SPD;
				}
				else
				{
					if (pDirection.x > -P_V_MAX_SPD * 0.75)
						pDirection.x -= 2.25f * dt;
					else
						pDirection.x = -P_V_MAX_SPD * 0.75;
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

		//Jumping * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

		this->isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		if (this->isSpacePressed == true && pIsJumping == false /*&& bottomCollision == true*/)
		{
			//If space was pressed, jump is started
  			pIsJumping = true;
			pDirection.y = -pJumpSpeed; //Negative because in SFML the x and y axises go from top left to bottom right, 
			botColliding = false;    //hence to jump "up" we need a negative direction
		}

		else if (botColliding == false)
		{
			//Apply gravity
			if (pDirection.y <= 0.0f)
				pDirection.y += (gGravity * dt);
			if (pDirection.y > 0.0f) 
			{
				if(pDirection.y < 5.0f)	pDirection.y += (1.68f * gGravity * dt);
				else pDirection.y = 5.0f;
			}
		}

		else 
			pIsJumping = false;

		this->Move(pDirection * pSpeed * dt);
		this->UpdateCollisionPoints();
			
	}

}

void Player::UpdateCollisionPoints()
{
	this->initPoints();
}

void Player::PrintCollPoints()
{
	for (int i = 0; i < 8; i++)
		std::cout << "cp" << i << ": " << " x: " << collPoints[i].x << " y: " << collPoints[i].y << std::endl;
	if (botColliding == true)
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
}

void Player::SetDirection(float x, float y)
{
	this->pDirection.x = x;
	this->pDirection.y = y;
}

void Player::SetXDirection(float x)
{
	this->pDirection = { x, pDirection.y };
}

void Player::SetYDirection(float y)
{
	this->pDirection = { pDirection.x, pDirection.y };

}

void Player::SetCollDir(int dir) //0 top 1 bottom 2 left 3 right
{

	if (dir == 0)
	{
		this->topColliding = true;
		this->botColliding = false;
	}
	else if (dir == 1)
	{
		this->rightColliding = true;
		this->leftColliding = false;
	}
	else if (dir == 2)
	{
		this->topColliding = false;
		this->botColliding = true;
	}
	if (dir == 3)
	{
		this->leftColliding = true;
		this->rightColliding = false;
	}
}

void Player::SetYPos(float x)
{
	Entity::SetPos({ x, this->GetY() });
	this->gravity = false;
}

void Player::DrawCollPoints(sf::RenderTarget & win)
{
	sf::CircleShape point;
	point.setFillColor(sf::Color::Red);
	point.setRadius(4.0f);
	point.setOrigin(4.0f, 4.0f);
	for (uint i = 0; i < 8; i++)
	{
		point.setPosition(this->collPoints[i]);
	    point.setOrigin({ this->collPoints[i].x, this->collPoints[i].y });
		win.draw(point);
	}
}

void Player::ShowCollPoints()
{
	this->showCollPoints = true;
}

void Player::HideCollPoints()
{
	this->showCollPoints = false;
}

void Player::initPoints() // 0 top 1 bot 2 left 3 right
{
	sf::Vector2f pCenter = this->GetPosition();//{this->GetPosition().x / 2, this->GetPosition.y / 2};
	sf::Vector2f pSize	 = this->GetSpriteSize();
	pCenter = sf::Vector2f(pCenter.x, pCenter.y);

	for (uint i = 0; i < 8; i++)
		collPoints[i] = pCenter;

	collPoints[0] = pCenter + sf::Vector2f{ pSize.x / 4.0f, -pSize.y / 2.0f };
	collPoints[1] = pCenter + sf::Vector2f{ pSize.x / 4.0f, -pSize.y / 2.0f };
	collPoints[2] = pCenter + sf::Vector2f{ pSize.x / 2.0f, -pSize.y / 4.0f };
	collPoints[3] = pCenter + sf::Vector2f{ pSize.x / 2.0f,  pSize.y / 4.0f };
	collPoints[4] = pCenter + sf::Vector2f{ pSize.x / 4.0f,  pSize.y / 2.0f };
	collPoints[5] = pCenter + sf::Vector2f{ -pSize.x / 4.0f,  pSize.y / 2.0f };
	collPoints[6] = pCenter + sf::Vector2f{ -pSize.x / 2.0f, -pSize.y / 4.0f };
	collPoints[7] = pCenter + sf::Vector2f{ -pSize.x / 2.0f,  pSize.y / 4.0f };
}

void Player::Reset()
{
	this->active = true;
	// Movement variables
	this->SetPos({ 0.0f, 0.0f });
	this->pDirection = { 0.0f, 0.0f };
	this->pWasSpacePressed = false;
	this->pIsJumping = false;
	//Collision Variables
	this->NoColl();
	this->initPoints();
}


bool Player::IsJumping() const
{
	return this->pIsJumping;
}

void Player::SetTopColl(bool coll)
{
	this->topColliding = coll;
}

void Player::SetBotColl(bool coll)
{
	this->botColliding = coll;
}

void Player::SetRightColl(bool coll)
{
	this->rightColliding = coll;
}

void Player::SetLeftColl(bool coll)
{
	this->leftColliding = coll;
}

bool Player::CollBot() const
{
	return this->botColliding;
}

bool Player::CollTop() const
{
	return this->botColliding;
}

bool Player::CollLeft() const
{
	return this->leftColliding;
}

bool Player::CollRight() const
{
	return this->rightColliding;
}

sf::Vector2f Player::GetPos()const { return this->GetPosition(); }

sf::Vector2f Player::GetDirection() const { return this->pDirection; }

sf::Vector2f Player::GetCollPointPos(int i)const{return this->collPoints[i];}

sf::FloatRect Player::GetGlobalBounds() const{ return Entity::GetGlobalBounds();}