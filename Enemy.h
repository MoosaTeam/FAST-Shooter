#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<vector>

#include "Timer.h"
#include "Player.h"
#include "EnemyProjectile.h"

using namespace std;
using namespace sf;

class Player;
class EnemyProjectile;

class Enemy {
protected:
	
	Clock clock;
	Texture enemyTexture;
	RectangleShape healthBarBG;
	RectangleShape healthBar;

	vector<EnemyProjectile*> enemyProjectileList;
	string enemyProjectileTexturePath;

public:

	Enemy(int enemyType);
	~Enemy();

	int health;
	float delay = 0;
	Sprite enemySprite;
	bool right = true;
	int type;
	int y;
	int playerX;
	int PlayerY;
	bool isNormal;
	int chance;
	bool isPlayerRewarded = false;
	int dropChance;
	int randomChance = 80;
	EnemyProjectile* upgrade;
	EnemyProjectile* enemyDeadCheck;

	void enemyUI(RenderWindow& window);
	void SetEnemy(int enemyType);
	void Update();
	virtual void Move();
	bool Die();
	int randRange(int low, int high);
	void Shoot(RenderWindow& window, Player* player);

};