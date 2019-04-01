#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "TerrainHandler.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT), "Squaredude 64");
	sf::Event event;
	Game game;
	sf::Clock clock;
	float dt = 0.0f;
	float tot = 9.0f;
	
	while (window.isOpen())
	{
		
		dt = clock.restart().asSeconds();
		tot += dt;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		game.Update(dt*GAMESPEED);
		game.Draw(window);
		if (tot > 10) 
		{
			game.Print();
			tot = 0.0f;
		}
		window.display();
	}
	return EXIT_SUCCESS;
}