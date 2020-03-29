#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "Game.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <fstream>

enum GameState { Running, Paused, Game_Over, Menu };

class GameHandler 
{
private:
	Game game;
	sf::Clock gClock;
	sf::RenderWindow gWindow;
	sf::Event event;

public:
	GameHandler();
	~GameHandler();
	//Functions
	void Run();
	void SaveHiScore();
	void LoadHiScore();

};
#endif // !GAMEHANDLER_H
