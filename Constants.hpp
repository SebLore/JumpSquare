#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//Misc. constants
#define PI 3.141592f //Pi
//Game constants
#define FPS 60	//Framerate
#define TCAP 7//10 //Max number of terrain objects
#define CCAP 12 //Number of coins
#define GAMESPEED 1.0f //Gamespeed.
//Window constants
#define WINDOW_WIDTH   800.0f
#define WINDOW_WIDTHI  800
#define WINDOW_HEIGHT  600.0f
#define WINDOW_HEIGHTI 600
#define WINDOW_CENTER  sf::Vector2f {WINDOW_WIDTH/2, WINDOW_HEIGHT/2}
#define WINDOW_CENTERI sf::Vector2f {WINDOW_WIDTHI/2, WINDOW_HEIGHTI/2}
#define ASPECT_RATIO   WINDOW_WIDTH/WINDOW_HEIGHT
//Player Constants
#define PLAYER_IDLE		sf::IntRect{0,0,12,32}, sf::Vector2f(WINDOW_CENTER), "../Resources/character/idle.png"
#define PLAYER_IDLE_DBG sf::IntRect{0,0,12,32}, sf::Vector2f(WINDOW_CENTER), "../Resources/character/idle.png" 
#define P_SPRITE_SIZE	sf::Vector2f {40, 40}
#define P_V_MAX_SPD		2.5f //Maximum vertical velocity
#define P_H_MAX_SPD		2.0f //Maximum horizontal velocity
//Terrain constants
#define PLATFORM		sf::Vector2f {100, 20}			//defines a platform [=====]
#define PLATFORM_LONG	sf::Vector2f {200, 20}	//defines a long platform [==========]

#define uint unsigned int

//PC Sprite Paths
#define PLAYER_SPRITE_IDLE "../Resources/character/elise_idle@2x.png" //Character sprite idle sheet
#define PLAYER_SPRITE_WALK "../Resources/character/elise_walk@2x.png" //Character sprite walk sheet
#define PLAYER_SPRITE_JUMP "../Resources/character/elise_jump@2x.png" //Character sprite jump sheet

//Enemy Sprite Path

//Terrain Texture paths
#define TERRAIN_TILESET_WIDTH 112.0f;
#define TERRAIN_TILESET_HEIGHT 176.0f
#define TERRAIN_TILESET "../Resources/terrain/terrain-tileset.png"
#define TERRAIN_GRASS_BLOCK_FULL "../Resources/terrain/terrain-tileset.png", {0,0, 48, 48}
//Coin texture path
#define COIN_SPRITE_WIDTH  700.0f
#define COIN_SPRITE_HEIGHT 200.0f
#define COIN_SPRITE "../Resources/coin/coin.png"
#define COIN_ROTATION1 {0,0, 116, 200}
#define COIN_ROTATION2
#define COIN_ROTATION3
#define COIN_ROTATION4
#define COIN_ROTATION5
#define COIN_ROTATION6
//#define COIN_SPRITE "../Resources/coin.png"
//Gameplay constants
const float gGravity	= 10.0f;
const float pMaxVSpeed  = 2.5f;
const float pMaxHSpeed  = 2.0f;
const float pJumpSpeed  = 4.0f;
const float pSpeed		= 180.0f;
const sf::Vector2f pStartPos{ 60.0f, 20.0f };


#endif // !1
