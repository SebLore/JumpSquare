#ifndef CONSTANTS_H
#define CONSTANTS_H

//Misc. constants
#define uint unsigned int
#define PI 3.141592f //F
//Game constants
#define FPS 60
#define TCAP 10 //Terraincap
#define GAMESPEED 1.0f
//Window constants
#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f
//Player Constants
#define PSPRITESIZE sf::Vector2f {40, 40}
#define P_VERT_MAX_SPD 2.5f //Maximum vertical velocity
#define P_H_MAX_SPD 2.0f
//Terrain constants
#define PLATFORM sf::Vector2f {100, 40}
//Gameplay constants
const float gGravity	= 10.0f;
const float pJumpSpeed  = 4.0f;


const sf::Vector2f topLeftColl  = { 5.0f, 0.0f };
const sf::Vector2f topRightColl = { 35.0f, 0.0f };
const sf::Vector2f botLeftColl  = { 5.0f, 40.0f };
const sf::Vector2f botRightColl = { 35.0f, 40.0f };
const sf::Vector2f leftTopColl  = { 0.0f, 5.0f };
const sf::Vector2f leftBotColl  = { 0.0f, 35.0f };
const sf::Vector2f rightTopColl = { 40.0f, 5.0f };
const sf::Vector2f rightBotColl = { 40.0f, 35.0f };

#endif // !1
