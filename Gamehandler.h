#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameHandler 
{
private:
	Game game;
	sf::Clock gClock;
public:
	GameHandler() {};
	~GameHandler() {};
	
	//Functions
	void RunGame();


};
#endif // !GAMEHANDLER_H
