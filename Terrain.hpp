#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "SFML/Graphics.hpp"
#include "Constants.hpp"

class Terrain : public sf::Drawable
{
private:
	//sf::Vector2f dimensions;
	sf::RectangleShape rect;
	sf::Texture tex;
	std::string texpath;
	bool isEnabled;
public:
	Terrain(sf::Vector2f size = { 0,0 }, sf::Vector2f position = { 0,0 }, sf::IntRect rect = sf::IntRect(), std::string texpath = TERRAIN_TILESET);
	~Terrain();
	Terrain(const Terrain &origObj);
	Terrain &operator=(const Terrain &copyObj);
	/*bool & operator==(const Terrain &compObj)const;
	bool & operator!=(const Terrain &compObj)const;*/
	//Functions
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Enable();
	void Disable();
	void EnableOutline();
	void SetScale(sf::Vector2f newscale);
	void SetScale(float x, float y);
	void SetTex(sf::Texture newtex);
	void SetTex(std::string newtexpath);
	void SetRepeated(bool input=true);
	void SetSize(sf::Vector2f newsize);
	void SetPosition(sf::Vector2f newposition);
	void SetColor(sf::Color newcolor);
	void SetX(float newx);
	void SetY(float newy);
	float GetX()const;
	float GetY()const;
	sf::RectangleShape	GetRect()const;
	sf::Texture			GetTex()const;
	sf::Vector2f GetPos()const;
	sf::Vector2f GetSize()const;
	sf::FloatRect GetGlobalBounds()const;
};
#endif // !TERRAIN_H
