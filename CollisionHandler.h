#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Constants.h"
#include "SFML\Graphics.hpp"
template <typename T>
class CollisionHandler 
{
private:
	T** objects;
	uint sizeofobjects;
	
public:
	CollisionHandler();
	~CollisionHandler();

};


#endif