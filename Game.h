#ifndef GAME_HPP
#define GAME_HPP

#include <SFML\Graphics.hpp>
#include "Player.h" 
#include "Terrain.h"
#include "EnemyHandler.h"
#include "Coin.h"
#include <iostream>

enum collision {NA, TOP, RIGHT, BOTTOM, LEFT};
enum GameState {Running, Paused, Game_Over, Menu};

class Game
{
private:
	sf::Text textPosition, textDirection;
	sf::Font font;
	sf::View gView;
	Player gPlayer;
	Terrain terrain[TCAP];
	EnemyHandler gEnemies;
	Coin coin;
	float deltaT= 0;
	
	bool textEnabled	= false;
	bool wasTextEnabled = false;

	bool EnemyCollision(Player &player, sf::FloatRect enemyBounds);
	void CollisionCheck(float dt);
	void TerrainCollision(Player &player, Terrain &terrain);
	//Init functions
	void InitPlayer();
	void InitTerrain();
	void InitEnemies();
	void InitCoins();
	void InitView(sf::RenderTarget &window);
	void UpdateView();

public:
	Game(Player player = sf::Vector2f{10, 360});
	~Game();
	void Update(float dt);
	void Draw(sf::RenderTarget &window);
	void Print();
	void Reset();
};

#endif