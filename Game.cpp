#include "Game.hpp"
Game::Game()
{
	this->paused = false;
	this->gPlayer = Player(PLAYER_IDLE);
	this->gEvent = sf::Event();
	this->font	 = sf::Font();
	this->gView  = sf::View();
	this->InitGame();
	this->score = 10000;
	this->hiscore = 0;
}

Game::~Game()
{
}

void Game::InitGame()
{
	this->gPlayer.ShowCollPoints();
	this->InitPlayer();
	this->InitText();
	this->InitCoins();
	this->InitTerrain();
	this->resetView();

	this->gBackgroundTexture.loadFromFile("../Resources/background.png");
	//	this->gBackgroundTexture.setRepeated(true);
	this->gBackgroundRect.setTexture(&this->gBackgroundTexture);
	this->gBackgroundRect.setPosition({ 0,0 });
	this->gBackgroundRect.setSize({ 10000, 2000 });
}

void Game::InitText()
{
	if (this->font.loadFromFile("../Resources/fonts/cour.ttf"))
	{
		this->textDirection.setFont(font);
		this->textPosition.setFont(font);
	}
	else 
		std::cout << "Font couldn't be loaded." << std::endl;

	this->textDirection.setString("");
	this->textPosition.setString("");
	this->textDirection.setColor(sf::Color::Red);
	this->textPosition.setColor(sf::Color::White);
}

void Game::DisplayHiScore()
{

}

void Game::InitPlayer(){
	gPlayer.SetScale(1.0f, 1.0f);
	gPlayer.SetPos(0.0f, 0.0f);
	gPlayer.Reset(); 
}

void Game::InitTerrain()
{
	terrain[0] = Terrain({ 500, 400}, { -40, gPlayer.GetSpriteSize().y }, sf::IntRect(0,0,48,48));
	terrain[1] = Terrain({ -1000, -1000 }, { -20, WINDOW_HEIGHT}, sf::IntRect(0, 0, 47, 47));
	terrain[2] = Terrain(PLATFORM_LONG, { 420, -50 }, sf::IntRect(0, 0, 48, 24));
	terrain[3] = Terrain(PLATFORM_LONG, { 800, -120 }, sf::IntRect(0, 0, 48, 24));
	terrain[4] = Terrain(PLATFORM_LONG, { 1100, -220 }, sf::IntRect(0, 0, 48, 24));
	terrain[5] = Terrain({ 500, 400 }, {1600, -40}, sf::IntRect(0, 0, 48, 48));
	//terrain[4] = Terrain({ 450, 150 }, PLATFORM, sf::IntRect(0, 0, 48, 48));
	/*for (int i = 0; i < TCAP; i++)
		terrain[i].EnableOutline();*/
}

//void Game::InitEnemies()
//{
//	gEnemies.AddEnemy( { 300, 360 } );
//	gEnemies.AddEnemy( { 450, 360 } );
//	gEnemies.AddEnemy( { 505, 110 } );
//}

void Game::InitCoins()
{
	for (int i = 0; i < CCAP; i++)
	{
		this->coins[i].SetTexture(COIN_SPRITE, {0,0,116,200});
		this->coins[i].SetScale(0.1f, 0.2f);
	}
	this->coins[0].SetPos(40.0f, -10.0f);
	this->coins[1].SetPos(55.0f, -10.0f);
	this->coins[2].SetPos(70.0f, -10.0f);
	this->coins[3].SetPos(471.0f, -100.0f);
	this->coins[4].SetPos(486.0f, -100.0f);
	this->coins[5].SetPos(501.0f, -100.0f);
	this->coins[6].SetPos(516.0f, -100.0f);
	this->coins[7].SetPos(531.0f, -100.0f);
	this->coins[8].SetPos(546.0f, -100.0f);
	this->coins[9].SetPos(360.0f, -10.0f);
	this->coins[10].SetPos(400.0f, -10.0f);
	this->coins[11].SetPos(440.0f, -10.0f);
	//this->coins[12].SetPos(480.0f, -20.0f);


}

void Game::resetView()
{
	gView.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	gView.setCenter({0,0});
	gView.rotate(0);
}

void Game::InitView(sf::RenderTarget &window)
{
	this->resetView();
	window.setView(gView);
}

void Game::UpdateView()
{
	sf::Vector2f currentView = gView.getCenter();
	sf::Vector2f pPos = gPlayer.GetPos();
	if (gPlayer.GetDirection().x == 0.0f)
	{
		if (pPos.x -50 < currentView.x - WINDOW_WIDTH / 2)
		{
			gView.setCenter(pPos.x + 150, currentView.y);
		}
	}
	else 
	{
		if (pPos.x - 200 < (currentView.x - (WINDOW_WIDTH / 2)) || pPos.x + 200 >(currentView.x + (WINDOW_WIDTH / 2)))
			gView.setCenter((currentView.x + gPlayer.GetDirection().x), currentView.y);
	}
	//gView.setCenter(pPos);
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(gView);
	target.draw(this->gBackgroundRect);
	for (int i = 0; i < TCAP; i++)
		target.draw(terrain[i], states);
	target.draw(this->gPlayer, states);
	for (int i = 0; i < CCAP; i++)
		target.draw(coins[i], states);

	//if (debugEnabled == true)
	//{
	//	target.draw(textDirection);
	//	target.draw(textPosition);
	//}
}

void Game::Update(float dt)
{
	if (this->paused == false && this->score > 0)
	{
		deltaT = deltaT - dt; //deltaT += dt;
		this->score -= dt;
		//Update player character between inputs
		this->gPlayer.Update(dt);
		//Check if player update made it collide/intersect with anything
		this->CollisionCheck(dt);

		/*Enemy Collision
		for (uint i = 0; i < gEnemies.GetNrOfEnemies(); i++)
		{
			if (gEnemies.GetGlobalBounds(i).intersects(gPlayer.GetGlobalBounds()))
			{
				if (gEnemies.IsActive(i))
				{
					if (EnemyCollision(gPlayer, gEnemies.GetGlobalBounds(i)))
					{
						gEnemies.Deactivate(i);
						gPlayer.SetDirection(gPlayer.GetDirection().x, -gPlayer.GetDirection().y / 1.5f);
					}
					else
						gPlayer.Deactivate();
				}
			}
		}*/

		//Coin Collision
		for (uint i = 0; i < CCAP; i++)
		{
			if (coins[i].IsActive())
			{
				if (coins[i].GetGlobalBounds().intersects(gPlayer.GetGlobalBounds()))
				{
					this->score += 1000;
					this->coins[i].Deactivate();
				}
			}
		}

		this->UpdateView();

		//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
		//	Debugging stuff

		//Enables/Disables text that displays player coordinates and speed/direction
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			if (debugEnabled)
				debugEnabled = false;
			else
				debugEnabled = true;
		}
		//Prints information if T has been pressed

		if (debugEnabled)
		{
			this->textDirection.setString
			(
				"x: " + std::to_string(gPlayer.GetDirection().x) +
				"\ny: " + std::to_string(gPlayer.GetDirection().y)
			);
			this->textPosition.setString
			(
				"x: " + std::to_string(gPlayer.GetPos().x) +
				"\ny: " + std::to_string(gPlayer.GetPos().y)
			);
			if (gPlayer.CollBot() == true)
				this->textDirection.setString(this->textDirection.getString() + "\nBottom is colliding!");
			if (gPlayer.IsJumping() == true)
				this->textDirection.setString(this->textDirection.getString() + "\nPlayer is jumping!");

			textDirection.setPosition(gView.getCenter().x - WINDOW_WIDTH / 2, gView.getCenter().y - WINDOW_HEIGHT / 2);
			textPosition.setPosition(gView.getCenter().x + WINDOW_WIDTH / 2 - 200, gView.getCenter().y - WINDOW_HEIGHT / 2);

		}
		//Resets the game if R is pressed or the player goes below y == 1000
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || gPlayer.GetY() > 1000.0f)
			this->Reset();
	}
	//else
}

void Game::Pause()
{
	this->paused = true;
}

void Game::Unpause()
{
	this->paused = false;
}

uint Game::GetScore()const
{
	this->score;
}

uint Game::GetHighScore() const
{
	return this->hiscore;
}

void Game::SetHighScore(uint hiscore)
{
	this->hiscore = hiscore;
}

void Game::CollisionCheck(float dt)
{
	sf::FloatRect tTemp;
	//int coll = -1;
	//Terrain collision

	for (uint i = 0; i < TCAP; i++)
	{
		tTemp = terrain[i].GetGlobalBounds();
		//See if player is colliding with smth above it
		if (tTemp.contains(gPlayer.GetCollPointPos(0)) || tTemp.contains(gPlayer.GetCollPointPos(1)))
		{
			gPlayer.SetCollDir(0);
			gPlayer.Move({ 0.0f, -gPlayer.GetDirection().y * dt * pSpeed });
			gPlayer.SetYDirection(0.0f);
		}
		//See if player is colliding with smth below it
		else if (tTemp.contains(gPlayer.GetCollPointPos(4)) || tTemp.contains(gPlayer.GetCollPointPos(5)))
		{
			gPlayer.SetCollDir(2);
			//gPlayer.SetBotColl(true);
			gPlayer.Move({ 0.0f, -gPlayer.GetDirection().y * dt * pSpeed });
			gPlayer.SetYDirection(0.0f);
		}
		else
		{
			/*gPlayer.SetTopColl(false);
			gPlayer.SetBotColl(false);*/
		}
		//See if player is colliding with smth to the right of it
		if (tTemp.contains(gPlayer.GetCollPointPos(2)) || tTemp.contains(gPlayer.GetCollPointPos(3)))
		{
			gPlayer.SetCollDir(1);
			gPlayer.Move({ -gPlayer.GetDirection().x * dt * pSpeed, 0.0f });
			gPlayer.SetXDirection(0.0f);
		}
		//See if player is colliding with smth to the left of it
		else if (tTemp.contains(gPlayer.GetCollPointPos(6)) || tTemp.contains(gPlayer.GetCollPointPos(7)))
		{
			gPlayer.SetCollDir(3);
			gPlayer.Move({ -gPlayer.GetDirection().x * dt * pSpeed, 0.0f });
			gPlayer.SetXDirection(0.0f);
		}
		else
		{
			gPlayer.SetRightColl(false);
			gPlayer.SetLeftColl(false);
		}
	}

	//Enemy Collision
	//for (uint i = 0; i < gEnemies.GetNrOfEnemies(); i++)
	//{
	//	if (gEnemies.GetGlobalBounds(i).intersects(gPlayer.GetGlobalBounds()))
	//	{
	//		if (gEnemies.IsActive(i))
	//		{
	//			if (EnemyCollision(gPlayer, gEnemies.GetGlobalBounds(i)))
	//			{
	//				gEnemies.Deactivate(i);
	//				gPlayer.SetDirection(gPlayer.GetDirection().x, -gPlayer.GetDirection().y / 1.5f);
	//			}
	//			else
	//				gPlayer.Deactivate();
	//		}
	//	}
	//}
	//Coin Collision
}


//bool Game::EnemyCollision(Player & player, sf::FloatRect enemyBounds)
//{
//	bool collision = false;
//	//See if player is colliding from above
//	if (enemyBounds.contains(player.GetCollPointPos(2)) || enemyBounds.contains(player.GetCollPointPos(3)))
//		collision = true;
//	else if
//		(
//			//From below
//			enemyBounds.contains(player.GetCollPointPos(0)) || enemyBounds.contains(player.GetCollPointPos(1)) ||
//			//From left
//			enemyBounds.contains(player.GetCollPointPos(4)) || enemyBounds.contains(player.GetCollPointPos(5)) ||
//			//From right
//			enemyBounds.contains(player.GetCollPointPos(6)) || enemyBounds.contains(player.GetCollPointPos(7))
//			)
//		player.Deactivate();
//	return collision;
//}

void Game::Reset()
{
	this->InitText();
	this->InitTerrain();
//	this->InitEnemies();
	this->InitCoins();
	this->gPlayer.Reset();
	this->resetView();
}