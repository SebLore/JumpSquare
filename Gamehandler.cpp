#include "Gamehandler.hpp"

GameHandler::GameHandler()
{
	this->gWindow.create(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Squaredude 64"); //= sf::RenderWindow(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Squaredude 64");
	this->game = Game();
	this->gClock = sf::Clock();
	this->event = sf::Event();
	LoadHiScore();
}

GameHandler::~GameHandler()
{
}

void GameHandler::Run()
{
	while (this->gWindow.isOpen())
	{
		while (gWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				gWindow.close();
			if (event.type == sf::Event::LostFocus) //Pause the game when you click outside the window
				game.Pause();
			if (event.type == sf::Event::GainedFocus) //Unpause when you click outside
				game.Unpause();
		}
		gWindow.clear(sf::Color::Blue);
		game.Update(gClock.restart().asSeconds()*GAMESPEED);
		gWindow.draw(game);
		gWindow.display();
	}
	
}

void GameHandler::SaveHiScore()
{
	std::ofstream file;
	std::string saveas = "hiscore.txt";

	file.open(saveas, std::fstream::out);

	if (file.is_open())
	{
		file << game.GetHighScore();
		file.close();
	}
}

void GameHandler::LoadHiScore()
{
	std::ifstream file;
	std::string filename = "hiscore.txt";
	uint contents = 0;

	file.open(filename, std::fstream::in);

	if (file.is_open()) 
	{
		file >> contents;
		file.close();
	}
	game.SetHighScore(contents);
}

