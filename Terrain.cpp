#include "Terrain.hpp"

Terrain::Terrain(sf::Vector2f size, sf::Vector2f position, sf::IntRect rect, std::string texpath)
{
	if (texpath != "")
	{
		this->tex.loadFromFile(texpath, rect);
	}
	this->rect.setTexture(&this->tex);
	this->rect.setPosition(position);
	this->rect.setSize(size);
	this->isEnabled = true;
}

Terrain::~Terrain()
{
}

Terrain::Terrain(const Terrain & origObj)
{
	this->rect		= origObj.rect;
	this->tex		= origObj.tex;
	this->isEnabled	= origObj.isEnabled;
}

Terrain & Terrain::operator=(const Terrain & copyObj)
{
	if(this != &copyObj)
	{ 
		this->rect		= copyObj.rect;
		this->tex		= copyObj.tex;
		this->rect.setTexture(&this->tex);
		this->isEnabled	= copyObj.isEnabled;
	}
	return *this;
}


void Terrain::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->rect, states);
}

void Terrain::Enable()
{
	this->isEnabled = true;
}

void Terrain::Disable()
{
	this->isEnabled = false;
}

void Terrain::EnableOutline()
{
	this->rect.setOutlineColor(sf::Color::Yellow);
	this->rect.setOutlineThickness(2.0f);
}

void Terrain::SetScale(sf::Vector2f newscale)
{
	this->rect.setScale(newscale);
}

void Terrain::SetScale(float x, float y)
{
	this->rect.setScale(x, y);
}

void Terrain::SetTex(sf::Texture newtex)
{
	this->tex = newtex;
	this->tex.setRepeated(true);
	this->rect.setTexture(&this->tex);
}

void Terrain::SetTex(std::string texpath)
{
	this->tex.loadFromFile(texpath);
	this->tex.setRepeated(true);
	this->texpath = texpath;
}

void Terrain::SetRepeated(bool input)
{
	this->tex.setRepeated(input);
	this->rect.setTexture(&this->tex);
}

void Terrain::SetSize(sf::Vector2f newsize)
{
	rect.setSize(newsize);
}

void Terrain::SetPosition(sf::Vector2f position)
{
	this->rect.setPosition(position);
}

void Terrain::SetColor(sf::Color newcolor)
{
	rect.setFillColor(newcolor);
}

void Terrain::SetX(float newx)
{
	this->rect.setPosition(newx, rect.getPosition().y);
}

void Terrain::SetY(float newy)
{
	this->rect.setPosition(this->rect.getPosition().x, newy);
}

float Terrain::GetX() const
{
	return rect.getPosition().x;
}

float Terrain::GetY() const
{
	return rect.getPosition().y;
}



sf::RectangleShape Terrain::GetRect() const
{
	return this->rect;
}

sf::Texture Terrain::GetTex() const
{
	return this->tex;
}

sf::Vector2f Terrain::GetPos() const
{
	return rect.getPosition();
}

sf::Vector2f Terrain::GetSize() const
{
	return this->rect.getSize();
}

sf::FloatRect Terrain::GetGlobalBounds() const
{
	return this->rect.getGlobalBounds();
}
