#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<fstream>

#include "Background.h"
#include "Timer.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "Menu.h"
#include "EnemyDiagonal.h"


using namespace sf;
using namespace std;

class EnemyProjectile;

class Game {

private:

	// Variables
	Texture gameOverTexture, btmTexture, retryTexture, resumeTexture, pauseTexture;
	Texture btmHoverTexture, retryHoverTexture, resumeHoverTexture;
	Sprite gameOverSprite, btmSprite, retrySprite, resumeSprite, pauseSprite;
	RectangleShape fadeScreen;
	RenderWindow* window;
	Timer time;
	Clock clock1;
	Clock enemyDeadClock;
	Player** players;
	int totalPlayers;
	int maxEnemies = 12;
	int enemies = 0;
	vector<Enemy*> enemylist;
	Background* background1;
	Background* background2;
	Vector2i mousePosWindow;
	bool isClicked = false;
	string option;
	bool isKilled = true;

	bool isGamePaused = false;

	Menu menu;
	int enemyType;
	int easyHighScore = 0, medHighScore = 0, hardHighScore = 0;
	ofstream hout;
	ifstream hin;

	SoundBuffer deathBuffer, enemyDeathBuffer;
	Sound deathSound, enemyDeathSound;
	bool deathSoundPlayed = false;

	Music titlebgMusic, gameoverMusic, easybgMusic, medbgMusic, hardbgMusic, pauseMusic;
	bool titlebgMusicPlaying = false;
	bool gameoverMusicPlaying = false;
	bool easybgMusicPlaying = false;
	bool medbgMusicPlaying = false;
	bool hardbgMusicPlaying = false;
	bool pauseMusicPlaying = false;

public:

	// Constructor / Destructor
	Game(int totalPlayers);
	~Game();

	// Functions
	void Run(); // Game Loop
	void SpawnEnemies(Player* player); // Creation of enemies and its functions
	int randRange(int low, int high); // Random number generator from low to high
	void pauseScreen();
};
