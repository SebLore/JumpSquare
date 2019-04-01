#include "Game.h"
Game::Game(Player player)
{
	if (!this->font.loadFromFile("../Resources/PWRectangular.ttf"))
		std::cout << "Font couldn't be loaded." << std::endl;
	this->Reset();
	textDirection.setFont(font);
	textPosition.setFont(font);
	textDirection.setString("");
	textDirection.setString("");
	textDirection.setColor(sf::Color::Red);
	textPosition.setColor(sf::Color::White);
	
}

Game::~Game()
{
}

void Game::InitPlayer(){ gPlayer.Reset(); }

void Game::InitTerrain()
{
	terrain[0] = Terrain({ -500, 0 }, { 500, 800 });
	terrain[1] = Terrain({ 0, 500 }, { WINDOW_WIDTH, 500 });
	terrain[2] = Terrain({ 450, 150 }, PLATFORM);
	terrain[3] = Terrain({ 120, 300 }, PLATFORM);
	terrain[4] = Terrain({ 400, 360 }, { 40, 40 });
}

void Game::InitEnemies()
{
	gEnemies.AddEnemy( { 300, 360 } );
	gEnemies.AddEnemy( { 450, 360 } );
	gEnemies.AddEnemy( { 505, 110 } );
}

void Game::InitCoins()
{
	coin.SetPos({ 100, 100 });
}

void Game::InitView(sf::RenderTarget &window)
{
	gView.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	gView.rotate(0);
	gView.setCenter({ WINDOW_WIDTH / 2 + 150, WINDOW_HEIGHT / 2});
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
		if (pPos.x - 150 < (currentView.x - (WINDOW_WIDTH / 2)) || pPos.x + 150  >(currentView.x + (WINDOW_WIDTH / 2)))
			gView.setCenter((currentView.x + gPlayer.GetDirection().x), currentView.y);
	}
}

void Game::Update(float dt)
{
	deltaT = deltaT - dt; //deltaT += dt;
	this->gPlayer.Update(dt);
	//Terrain Collision	
	this->CollisionCheck(dt);
	for (uint i = 0; i < TCAP; i++)
	{
		if (terrain[i].GetGlobalBounds().intersects(gPlayer.GetGlobalBounds()))
		{
			TerrainCollision(gPlayer, terrain[i]);
		}
	}
	//Enemy Collision
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
	}
	//Coin Collision

	this->UpdateView();
	//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	//	Debugging stuff

	//Enables/Disables text that displays player coordinates and speed/direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && deltaT < 0.5f)
	{
		if (textEnabled) {
			textEnabled = false;
			deltaT = 0.0f;
		}
		else
		{
			textEnabled = true;
			deltaT = 0.0f;
		}
	}
	//Prints information if T has been pressed
	if (textEnabled)
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

	textDirection.setPosition(gView.getCenter().x - WINDOW_WIDTH / 2, gView.getCenter().y - WINDOW_HEIGHT / 2);
	textPosition.setPosition( gView.getCenter().x + WINDOW_WIDTH / 2 - 200, gView.getCenter().y - WINDOW_HEIGHT / 2 );
	
	}
	//Resets the game if R is pressed or the player goes below y == 1000
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || gPlayer.GetY() > 1000.0f)
		this->Reset();
}

void Game::Draw(sf::RenderTarget &window)
{
	window.clear();
	gEnemies.DrawAll(window);
	for (uint i = 0; i < TCAP; i++)
		terrain[i].DrawTo(window);
	//coin.DrawTo(window);
	gPlayer.DrawTo(window);
	window.setView(gView);
	if(textEnabled)
	{
		window.draw(textDirection);
		window.draw(textPosition);
	}
	

}

void Game::CollisionCheck(float dt)
{
	//Terrain collision
	for (uint i = 0; i < TCAP; i++)
	{
		if (terrain[i].GetGlobalBounds().intersects(gPlayer.GetGlobalBounds()))
		{
			//If colliding: sort out which side of the player is colliding for the sake of movement
			TerrainCollision(gPlayer, terrain[i]);
		}
	}
	//Enemy Collision
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
	}
	//Coin Collision
}

void Game::TerrainCollision(Player & player, Terrain & terrain)
{
	//See if player is colliding with smth below it
	if (terrain.GetGlobalBounds().contains(player.GetCollPoint(0)) || terrain.GetGlobalBounds().contains(player.GetCollPoint(1)))
		player.SetCollDir(1, 0);
	else if (player.GetDirection().y == 0)
		player.SetCollDir(1, 1);

	//See if player is colliding with smth above it
	if (terrain.GetGlobalBounds().contains(player.GetCollPoint(2)) || terrain.GetGlobalBounds().contains(player.GetCollPoint(3)))
		player.SetCollDir(0);
	else if (player.GetDirection().y == 0)
		player.SetCollDir(0, 1);
	//See if player is colliding with smth to the left of it
	if (terrain.GetGlobalBounds().contains(player.GetCollPoint(4)) || terrain.GetGlobalBounds().contains(player.GetCollPoint(5)))
		player.SetCollDir(2);
	//See if player is colliding with smth to the right of it
	if (terrain.GetGlobalBounds().contains(player.GetCollPoint(6)) || terrain.GetGlobalBounds().contains(player.GetCollPoint(7)))
		player.SetCollDir(3);
	
}

bool Game::EnemyCollision(Player & player, sf::FloatRect enemyBounds)
{
	bool collision = false;
	//See if player is colliding from above
	if (enemyBounds.contains(player.GetCollPoint(2)) || enemyBounds.contains(player.GetCollPoint(3)))
		collision = true;
	else if
		(
			//From below
			enemyBounds.contains(player.GetCollPoint(0)) || enemyBounds.contains(player.GetCollPoint(1)) ||
			//From left
			enemyBounds.contains(player.GetCollPoint(4)) || enemyBounds.contains(player.GetCollPoint(5)) ||
			//From right
			enemyBounds.contains(player.GetCollPoint(6)) || enemyBounds.contains(player.GetCollPoint(7))
			)
		player.Deactivate();
	return collision;
}

void Game::Print()
{
	gPlayer.PrintPos();
	gPlayer.PrintCollPoints();
}

void Game::Reset()
{
	this->InitTerrain();
	this->InitEnemies();
	this->InitCoins();
	this->gPlayer.Reset();
	gView.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	gView.setCenter({ WINDOW_WIDTH / 2 + 150, WINDOW_HEIGHT / 2 });
}