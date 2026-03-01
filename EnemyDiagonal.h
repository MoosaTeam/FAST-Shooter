#pragma once

#include "Enemy.h"
#include<SFML/Graphics.hpp>

class Enemy;

class EnemyDiagonal : public Enemy
{
private:
	bool moveLeft;

public:
	EnemyDiagonal(int enemyType);
	~EnemyDiagonal();

	void Move();

};

