#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(float speed, string texturePath)
{
	this->speed = speed;
	if (texturePath == "Sprite/Upgrade1.png")
		upgrade = true;
	if (texturePath == "Sprite/Health1.png")
		healthUpgrade = true;
	if (!enemyProjectileTexture.loadFromFile(texturePath)) {}
	enemyProjectileSprite.setTexture(enemyProjectileTexture);
	enemyProjectileSprite.setScale(Vector2f(0.03, 0.03));
	enemyProjectileSprite.setOrigin(Vector2f(enemyProjectileSprite.getTexture()->getSize().x * 0.5, enemyProjectileSprite.getTexture()->getSize().y * 0.5));

	if (!upgradeBuffer.loadFromFile("Sounds/upgrade.wav")) {}
	upgradeSound.setBuffer(upgradeBuffer);
	upgradeSound.setVolume(20.f);
}


void EnemyProjectile::Colliding(Player* player, EnemyProjectile* enemyProjectile)
{
	if (enemyProjectileSprite.getGlobalBounds().intersects(player->hitbox.getGlobalBounds())) {
		if (!upgrade && !healthUpgrade)
			player->vulnerable = false;
		else if (healthUpgrade && player->health < 10)
		{
			upgradeSound.stop();
			upgradeSound.play();
			player->health += 1;
		}
		else
		{
			upgradeSound.stop();
			upgradeSound.play();
			if (player->upgradeCount < 9)
			{
				if (!player->swap)
				{
					player->swap = true;
					player->additionalDamage += 0.5;
				}
				else {
					player->swap = false;
					player->speed -= 0.05f;
				}
				player->upgradeCount++;
			}
		}

		enemyProjectile->collide = true;
		enemyProjectile->GetProjectileSprite().setPosition(0, -100);
	}
}

void EnemyProjectile::Update()
{
	enemyProjectileSprite.move(0, speed * timesec::deltaTime);
}

void EnemyProjectile::blinkDeadCheck(Enemy& enemy) {
	if (j >= 0)
	{
		enemy.enemyDeadCheck->GetProjectileSprite().setColor(Color(255, 255, 255, j));
		j--;
	}
}

Sprite& EnemyProjectile::GetProjectileSprite()
{
	return enemyProjectileSprite;
}

EnemyProjectile::~EnemyProjectile()
{
}
