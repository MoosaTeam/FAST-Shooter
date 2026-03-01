#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

#include "Timer.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

class Player;
class Enemy;

class Projectile {
private:

	Texture projectileTexture;
	Sprite projectileSprite;
	float speed;

public:
	
	Projectile(float speed, string texturePath);
	~Projectile();

	bool collide = false;

	void Colliding(vector<Enemy*> enemylist, Projectile* projectile, int enemyKoDamage);
	void Update();
	Sprite& GetProjectileSprite();

};
