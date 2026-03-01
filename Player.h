#pragma once

#include<SFML/Graphics.hpp>

#include<vector>
#include<iostream>
#include<string>
#include<fstream>

#include "Timer.h"
#include "Projectile.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

class Projectile;
class Enemy;

class Player {

private:
	Texture u[10];
	Sprite upgradeSprite;
	Texture playerTexture;
	Texture playerHurtTexture;
	Texture healthTexture;
	Font font;
	string status;
	Clock clock;
	int blinkCount = 0;
	float spriteTrans = 255;
	Vector2i mousePosWindow;

	std::vector<Projectile*> projectileList;
	string projectileTexturePath;

public:

	Player(int playerNum, string projectileTexturePath);
	~Player();

	int upgradeCount = 0;
	int playerNumber = 0;
	int health = 3;
	int score = 0;
	float x = 0, y = 0;
	float speed = 0.4f;
	Sprite playerSprite;
	Sprite healthSprite;
	bool vulnerable = true;
	Text text;
	RectangleShape hitbox;
	float enemyKoDamage = 1;
	float additionalDamage = 0;
	bool tookDamage = false;
	bool swap = false;

	void SetPlayer();
	void Collision(vector<Enemy*>& enemylist);
	void Blinking();
	void Shoot(RenderWindow& window, vector<Enemy*>& enemylist);
	void UI(RenderWindow& window, int& highScore);
	void UpdateInput(RenderWindow & window);
	void Update(RenderWindow& window, std::vector<Enemy*> &enemylist);

	SoundBuffer hurtBuffer, shootBuffer;
	Sound hurtSound, shootSound;

};