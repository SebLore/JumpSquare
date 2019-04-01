#include "SFML/Graphics.hpp"
#include "Constants.h"


#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain//: sf::Drawable
{
private:
	sf::Vector2f dimensions;
	sf::RectangleShape terrain;
	bool isEnabled;
public:
	Terrain(sf::Vector2f position = {}, sf::Vector2f size = {});
	~Terrain();
	Terrain(const Terrain &origObj);
	Terrain &operator=(const Terrain &copyObj);
	bool & operator==(const Terrain &compObj)const;
	bool & operator!=(const Terrain &compObj)const;
	//Functions
	void DrawTo(sf::RenderTarget &window);
	void Enable();
	void Disable();
	float GetX()const;
	float GetY()const;
	sf::Vector2f GetPos()const;
	sf::Vector2f GetSize()const;
	sf::FloatRect GetGlobalBounds()const;
};
#endif // !TERRAIN_H
