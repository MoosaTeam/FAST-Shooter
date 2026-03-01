#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>

#include "Timer.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

class Player;
class Enemy;

class EnemyProjectile {
private:

	Sprite enemyProjectileSprite;
	Texture enemyProjectileTexture;
	float speed;
	Clock clock;
	bool upgrade = false;
	bool healthUpgrade = false;
	bool swap = false;
	int j = 255;

	SoundBuffer upgradeBuffer;
	Sound upgradeSound;

public:

	EnemyProjectile(float speed, string texturePath);
	~EnemyProjectile();

	bool collide = false;

	void Colliding(Player* player, EnemyProjectile* enemyProjectile);
	void Update();
	Sprite& GetProjectileSprite();

	void blinkDeadCheck(Enemy& enemy);


};
