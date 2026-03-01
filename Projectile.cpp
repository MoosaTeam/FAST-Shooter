#include "Projectile.h"


Projectile::Projectile(float speed, string texturePath) {
	this->speed = speed;
	if (!projectileTexture.loadFromFile(texturePath)) {}
	projectileSprite.setTexture(projectileTexture);
	projectileSprite.setScale(Vector2f(0.03, 0.03));
	projectileSprite.setOrigin(Vector2f(projectileSprite.getTexture()->getSize().x * 0.5, projectileSprite.getTexture()->getSize().y * 0.5));
}

void Projectile::Colliding(vector<Enemy*> enemylist, Projectile* projectile, int enemyKoDamage) {
	for (size_t i = 0; i < enemylist.size(); i++)
	{
		if (projectileSprite.getGlobalBounds().intersects(enemylist[i]->enemySprite.getGlobalBounds())) {
			enemylist[i]->health -= enemyKoDamage;
			projectile->collide = false;
			projectileSprite.setPosition(0, -100);
		}
	}
}

void Projectile::Update() {
	projectileSprite.move(Vector2f(0, speed * timesec::deltaTime));
}

Sprite& Projectile::GetProjectileSprite() {
	return projectileSprite;
}

Projectile::~Projectile() {

}
