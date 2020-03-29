#ifndef GAME_HPP
#define GAME_HPP

#include <SFML\Graphics.hpp>
#include "Player.hpp" 
#include "Terrain.hpp"
#include "EnemyHandler.hpp"
#include "Coin.hpp"
#include "Constants.hpp"
#include <iostream>

enum collision {NA, TOP, RIGHT, BOTTOM, LEFT};

class Game : public sf::Drawable
{
private:
	sf::Event gEvent;
	sf::Text textPosition, textDirection, scoretxt, hiscoretxt, losetxt;
	sf::Font font;
	sf::View gView;
	Player gPlayer;
	Terrain terrain[TCAP];
	sf::Texture gBackgroundTexture;
	sf::RectangleShape gBackgroundRect;
	Coin coins[12];

	float deltaT; //Time
	uint score;
	uint hiscore;
	bool paused;
	bool debugEnabled;
	bool wasTextEnabled;
	bool drawPoints;
	//bool EnemyCollision(Player &player, sf::FloatRect enemyBounds);
	void CollisionCheck(float dt);
	//void TerrainCollision(Player &player, Terrain &terrain);
	//Initiation functions for the different classes
	void InitGame();
	void InitText();
	void DisplayHiScore();
	void DisplayScore();
	void InitPlayer();
	void InitTerrain();
	//void InitEnemies();
	void InitCoins();
	void InitView(sf::RenderTarget &window);
	void resetView();
	void UpdateView();
public:
	Game();
	~Game();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void Update(float dt);
	void Pause();
	void Unpause();
	uint GetScore()const;
	uint GetHighScore()const;
	void SetHighScore(uint hiscore);
	void Reset();
};

#endif