#include "Enemy.h"

Enemy::Enemy(int enemyType) {
	SetEnemy(enemyType);
	isNormal = true;
	enemyDeadCheck = new EnemyProjectile(90, "Sprite/enemy_exposion.png");
	enemyDeadCheck->GetProjectileSprite().setScale(0.3f, 0.3f);
	dropChance = randRange(0, 100);
	if (dropChance >= randomChance && dropChance < 95)
	{
		upgrade = new EnemyProjectile(100, "Sprite/Upgrade1.png");
		randomChance += 1;
	}
	else if (dropChance >= 95 && dropChance < 100)
	{
		upgrade = new EnemyProjectile(100, "Sprite/Health1.png");
	}

}

void Enemy::SetEnemy(int enemyType) {
	y = randRange(100, 300);
	if (enemyType >= 0 && enemyType < 200)
	{
		type = 1;
		health = 3;
		enemyTexture.loadFromFile("Sprite/small_enemy.png");
	}
	else if (enemyType >= 200 && enemyType < 800)
	{
		type = 2;
		health = 6;
		enemyTexture.loadFromFile("Sprite/mid_enemy.png");
	}
	else
	{
		type = 3;
		health = 10;
		enemyTexture.loadFromFile("Sprite/big_enemy.png");
	}
	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(Vector2f(0.05f, 0.05f));
	enemySprite.setOrigin(Vector2f(enemySprite.getTexture()->getSize().x * 0.5f, enemySprite.getTexture()->getSize().y * 0.5f));

	// set health bar
	healthBarBG.setFillColor(Color::White);
	healthBarBG.setSize(Vector2f(56.f, 16.f));
	
	healthBar.setFillColor(Color::Red);
	healthBar.setSize(Vector2f(50.0 / health, 10.f));

}

bool Enemy::Die() {
	if (health > 0)
		return false;
	else
	{
		return true;
	}
}

void Enemy::Move() {
	if (right)
		enemySprite.move(Vector2f(150.0f * timesec::deltaTime, 0));
	else
		enemySprite.move(Vector2f(-150.0f * timesec::deltaTime, 0));

	if (enemySprite.getPosition().y <= y)
		enemySprite.move(Vector2f(0.f, 150.f * timesec::deltaTime));

	if (enemySprite.getPosition().x <= 50)
		right = true;
	else if (enemySprite.getPosition().x >= 550)
		right = false;
}

void Enemy::Shoot(RenderWindow& window, Player* player) {
	Time elapsed = clock.getElapsedTime();
	float elapsedTime;
	if (type == 1)
		elapsedTime = 2.f;
	else if (type == 2)
		elapsedTime = 1.5f;
	else
		elapsedTime = 1.f;
	if (elapsed >= seconds(elapsedTime)) {
		EnemyProjectile* enemyProjectile;
		enemyProjectile = new EnemyProjectile(250, "Sprite/enemy_shoot.png");
		enemyProjectile->GetProjectileSprite().setPosition(Vector2f(this->enemySprite.getPosition().x, this->enemySprite.getPosition().y + 33));
		enemyProjectileList.push_back(enemyProjectile);
		clock.restart();
	}


	for (size_t i = 0; i < enemyProjectileList.size(); i++)
	{
		if (enemyProjectileList[i]->collide != true && enemyProjectileList[i]->GetProjectileSprite().getPosition().y <= 800 && enemyProjectileList[i]->GetProjectileSprite().getPosition().x > 0) {
			window.draw(enemyProjectileList[i]->GetProjectileSprite());
			enemyProjectileList[i]->Update();
			enemyProjectileList[i]->Colliding(player, enemyProjectileList[i]);
		}
		else if (enemyProjectileList[i]->GetProjectileSprite().getPosition().y >= 800 || enemyProjectileList[i]->GetProjectileSprite().getPosition().x == 0) {
			delete enemyProjectileList[i];
			enemyProjectileList.erase(enemyProjectileList.begin() + i);
		}
	}
}

int Enemy::randRange(int low, int high)
{
	return rand() % (high - low) + low;
}

void Enemy::enemyUI(RenderWindow& window) {
	healthBarBG.setPosition(enemySprite.getPosition().x - 29, enemySprite.getPosition().y - 55);
	window.draw(enemySprite);
	window.draw(healthBarBG);
	for (int i = 0; i < health; i++) {
		healthBar.setPosition((healthBarBG.getPosition().x) + (i * healthBar.getSize().x) + 3, healthBarBG.getPosition().y + 3);
		window.draw(healthBar);
	}

}

void Enemy::Update() {
	Move();
}

Enemy::~Enemy() {

}

