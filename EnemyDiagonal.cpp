#include "EnemyDiagonal.h"

EnemyDiagonal::EnemyDiagonal(int enemyType) : Enemy(enemyType) {
	moveLeft = rand() % 2;
	isNormal = false;
}

void EnemyDiagonal::Move() {
	enemySprite.move(Vector2f(0, 200.0f * timesec::deltaTime));
	if (moveLeft) {
		enemySprite.move(Vector2f(-200.0f * timesec::deltaTime, 0));
		if (enemySprite.getPosition().x <= 50)
		{
			moveLeft = false;
		}
	}
	else
	{
		enemySprite.move(Vector2f(200.0f * timesec::deltaTime, 0));
		if (enemySprite.getPosition().x >= 550) {
			moveLeft = true;
		}
	}

	if (enemySprite.getPosition().y >= 850)
		enemySprite.setPosition(enemySprite.getPosition().x, -50);
}

EnemyDiagonal::~EnemyDiagonal() {

}