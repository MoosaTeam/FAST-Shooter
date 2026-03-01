#include "Player.h"

// constructor
Player::Player(int playerNum, string projectileTexturePath) {
	playerNumber = playerNum;
	this->projectileTexturePath = projectileTexturePath;
	SetPlayer();
	if (playerNumber = 1) {
		x = 300;
		y = 700;
	}
	if (!hurtBuffer.loadFromFile("Sounds/hurt.wav")) {}
	hurtSound.setBuffer(hurtBuffer);
	hurtSound.setVolume(10.f);

	if (!shootBuffer.loadFromFile("Sounds/shoot.wav")) {}
	shootSound.setBuffer(shootBuffer);
	shootSound.setVolume(10.f);
}

void Player::SetPlayer() {

	// player upgrade bar
	for (int i = 0; i < 10; i++) {
		u[i].loadFromFile("Sprite/(GUI) UPGRADE " + to_string(i + 1) + ".png");
	}
	upgradeSprite.setScale(2.f, 2.f);
	upgradeSprite.setPosition(27.5f, 700.f);

	// player score font
	if (!font.loadFromFile("Fonts/ThaleahFat.ttf")) {}
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(25);
	text.setPosition(10, 10);

	// player health texture
	if (!healthTexture.loadFromFile("Sprite/(GUI) heart.png")) {}
	healthSprite.setTexture(healthTexture);
	healthSprite.setScale(Vector2f(0.1, 0.1));
	healthSprite.setOrigin(Vector2f(healthSprite.getTexture()->getSize().x * 0.5, healthSprite.getTexture()->getSize().y * 0.5));
	
	// Set sprite for player
	if (playerNumber == 1) {
		if (!playerTexture.loadFromFile("Sprite/Player1.png")) {}
		if (!playerHurtTexture.loadFromFile("Sprite/ship_hurt.png")) {}
		status = "Score: ";
	}

	// set hitbox
	hitbox.setSize(Vector2f(24.75f, 24.75f));

	// creation of player
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(Vector2f(0.05, 0.05));
	playerSprite.setOrigin(Vector2f(playerSprite.getTexture()->getSize().x * 0.5, playerSprite.getTexture()->getSize().y * 0.5));
	playerSprite.setPosition(300.f, 700.f);
}

// shoot function
void Player::Shoot(RenderWindow& window, vector<Enemy*>& enemylist) {
	// get position window
	mousePosWindow = Mouse::getPosition(window);
	Time elapsed = clock.getElapsedTime();

	// if left mouse button is pressed, create a bullet
	if (Mouse::isButtonPressed(Mouse::Left) && elapsed >= seconds(speed)) {
		if (rand() % 2)
			shootSound.setPitch(1.f);
		else
			shootSound.setPitch(1.1f);
		shootSound.stop();
		shootSound.play();
		Projectile* projectile = new Projectile(-1200, projectileTexturePath);
		projectile->GetProjectileSprite().setPosition(Vector2f(mousePosWindow.x - 2, mousePosWindow.y-33));
		projectileList.push_back(projectile);
		clock.restart();
	}

	// for every projectile, do
	for (size_t i = 0; i < projectileList.size(); i++)
	{
		if (projectileList[i]->collide != true && projectileList[i]->GetProjectileSprite().getPosition().y >= 0) {
			window.draw(projectileList[i]->GetProjectileSprite());
			projectileList[i]->Update();
			projectileList[i]->Colliding(enemylist, projectileList[i], (enemyKoDamage + additionalDamage));
		}

		if (projectileList[i]->GetProjectileSprite().getPosition().y <= 0) {
			delete projectileList[i];
			projectileList.erase(projectileList.begin() + i);
		}
	}
}

// collision with enemy
void Player::Collision(vector<Enemy*>& enemylist) {
	for (size_t i = 0; i < enemylist.size(); i++)
	{
		if (hitbox.getGlobalBounds().intersects(enemylist[i]->enemySprite.getGlobalBounds())) {
			vulnerable = false;
		}
	}
}

void Player::Blinking() {
	if (blinkCount < 20) {
		playerSprite.setTexture(playerHurtTexture);
		if (blinkCount % 2 != 0) {
			spriteTrans += 3000 * timesec::deltaTime;
			if (spriteTrans >= 255) {
				spriteTrans = 255;
				blinkCount++;
			}
			playerSprite.setColor(Color(255, 255, 255, 255));
		}
		else {
			spriteTrans -= 3000 * timesec::deltaTime;
			if (spriteTrans <= 50) {
				spriteTrans = 50;
				blinkCount++;
			}
			playerSprite.setColor(Color(255, 255, 255, 0));
		}
	}
	else {
		playerSprite.setTexture(playerTexture);
		blinkCount = 0;
		tookDamage = false;
		vulnerable = true;
	}
}

void Player::UI(RenderWindow& window, int& highScore) {
	for (size_t i = 0; i < health; i++)
	{
		healthSprite.setPosition(Vector2f(50 * (i + 1), 755));
		window.draw(healthSprite);
	}
	text.setString(status + to_string(score) + "\nHigh Score: " + to_string(highScore));
	window.draw(text);

	upgradeSprite.setTexture(u[upgradeCount]);
	window.draw(upgradeSprite);
}

void Player::UpdateInput(RenderWindow& window) {
	mousePosWindow = Mouse::getPosition(window);
	if (mousePosWindow.x <= 33.f)
		playerSprite.setPosition(33.0f, static_cast<float>(mousePosWindow.y));
	else if (mousePosWindow.x >= 567.f)
		playerSprite.setPosition(567.f, static_cast<float>(mousePosWindow.y));
	else if (mousePosWindow.y <= 33.f)
		playerSprite.setPosition(static_cast<float>(mousePosWindow.x), 33.0f);
	else if (mousePosWindow.y >= 767.f)
		playerSprite.setPosition(static_cast<float>(mousePosWindow.x), 767.f);
	else
		playerSprite.setPosition(static_cast<float>(mousePosWindow.x), static_cast<float>(mousePosWindow.y));
	
	hitbox.setPosition(Vector2f(playerSprite.getPosition().x - (hitbox.getSize().x / 2), playerSprite.getPosition().y - (hitbox.getSize().y / 2)));
}


void Player::Update(RenderWindow& window, std::vector<Enemy*> &enemylist) {
	if (health > 0) {
		Shoot(window, enemylist);
		if (vulnerable) {
			hurtSound.stop();
			UpdateInput(window);
			Collision(enemylist);
			window.draw(playerSprite);
		}
		else {
			UpdateInput(window);
			if (!tookDamage) {
				hurtSound.play();
				health--;
				tookDamage = true;
			}
			Blinking();
			window.draw(playerSprite);
		}
	}
	else {
		playerSprite.setPosition(Vector2f(-640, y));
		status = "Dead\nScore: ";
	}
}

Player::~Player() {
	
}

