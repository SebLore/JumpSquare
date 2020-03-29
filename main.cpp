#include <SFML/Graphics.hpp>
#include "Gamehandler.hpp"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameHandler gh;
	gh.Run();
	return EXIT_SUCCESS;
	//sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTHI, WINDOW_HEIGHTI), "Laboration DV1497");
	//sf::Event event = sf::Event{};
	////Game game;
	//sf::Clock clock;
	//while (window.isOpen())
	//{
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed) 
	//			window.close();
	//		//if (event.type == sf::Event::LostFocus) //Pause the game when you click outside the window
	//		//	game.Pause();
	//		//if (event.type == sf::Event::GainedFocus) //Unpause when you click outside
	//		//	game.Unpause();
	//	}
	//	window.clear();
	//	//game.Update(clock.restart().asSeconds()*GAMESPEED);
	//	//window.draw(game);
	//	window.display();
	//}
}