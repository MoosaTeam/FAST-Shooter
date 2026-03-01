#include "Game.h"

using namespace sf;
using namespace std;

// Constructor
Game::Game(int totalPlayers = 1) {
	// Window creation
	window = new RenderWindow(VideoMode(600, 800), "Space Shooter", Style::Titlebar | Style::Close);

	// Assigning players
	this->totalPlayers = totalPlayers;

	// Creates player
	players = new Player * [totalPlayers];
	players[0] = new Player(1, "Sprite/shoot.png");

	// Creates background
	background1 = new Background(0);
	background2 = new Background(-800);

	// Creates gameover screen
	if (!gameOverTexture.loadFromFile("Sprite/(GUI) game over.png")) {}
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setPosition(148, 100);

	// Sets properties for the gameover screen
	fadeScreen.setSize(Vector2f(600.f, 800.f));
	fadeScreen.setFillColor(Color(0, 0, 0, 0));
	fadeScreen.setPosition(Vector2f(0, 0));

	if (!pauseTexture.loadFromFile("Sprite/GUI_paused_screen.png")) {}
	pauseSprite.setTexture(pauseTexture);

	if (!resumeTexture.loadFromFile("Sprite/(GUI) RESUME (UNCLICKED).png")) {}
	if (!resumeHoverTexture.loadFromFile("Sprite/(GUI) RESUME (HOVER).png")) {}
	resumeSprite.setTexture(resumeTexture);

	if (!btmTexture.loadFromFile("Sprite/(GUI) BACKTOMENU (UNCLICKED).png")) {}
	if (!btmHoverTexture.loadFromFile("Sprite/(GUI) BACKTOMENU (HOVER).png"))
	btmSprite.setTexture(btmTexture);
	if (!retryTexture.loadFromFile("Sprite/(GUI) RETRY (UNCLICKED).png")) {}
	if (!retryHoverTexture.loadFromFile("Sprite/(GUI) RETRY (HOVER).png"))
	retrySprite.setTexture(retryTexture);

	resumeSprite.setScale(3.f, 3.f);
	btmSprite.setScale(3.f, 3.f);
	retrySprite.setScale(3.f, 3.f);

	resumeSprite.setPosition(193.5f, 490.f);
	retrySprite.setPosition(Vector2f(208.5f, 490.f));
	btmSprite.setPosition(Vector2f(132.f, 550.f));


	// file handling

	hin.open("High Score.txt");
	hin >> easyHighScore >> medHighScore >> hardHighScore;
	hin.close();

	hout.open("High Score.txt");
	hout << 0 << endl << 0 << endl << 0 << endl;
	hout.close();

	hout.open("High Score.txt");

	// Sound loading
	if (!deathBuffer.loadFromFile("Sounds/death.wav")) {}
	deathSound.setBuffer(deathBuffer);
	deathSound.setVolume(5.f);

	if (!enemyDeathBuffer.loadFromFile("Sounds/enemy death.wav")) {}
	enemyDeathSound.setBuffer(enemyDeathBuffer);
	enemyDeathSound.setVolume(10.f);

	if (!titlebgMusic.openFromFile("Sounds/title bg music.mp3")) {}
	titlebgMusic.setLoop(true);
	titlebgMusic.setVolume(10.f);

	if (!gameoverMusic.openFromFile("Sounds/game over bg music.mp3")) {}
	gameoverMusic.setLoop(true);
	gameoverMusic.setVolume(4.f);

	if (!easybgMusic.openFromFile("Sounds/easy difficulty bg music.mp3")) {}
	easybgMusic.setLoop(true);
	easybgMusic.setVolume(3.f);

	if (!medbgMusic.openFromFile("Sounds/medium difficulty bg music.mp3")) {}
	medbgMusic.setLoop(true);
	medbgMusic.setVolume(1.f);

	if (!hardbgMusic.openFromFile("Sounds/hard difficulty bg music.mp3")) {}
	hardbgMusic.setLoop(true);
	hardbgMusic.setVolume(2.f);

	if (!pauseMusic.openFromFile("Sounds/pause bg music.mp3")) {}
	pauseMusic.setVolume(1.f);
	pauseMusic.setLoop(true);
}

// Runs the game
void Game::Run() {

	// game loop
	while (window->isOpen()) {
		time.Update();

		// Poll Events
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				hout << easyHighScore << endl << medHighScore << endl << hardHighScore;
				hout.close();
				window->close();
				break;
			}
		}

		// disable the mouse visibility

		if (players[0]->health > 0 && !isGamePaused) {
			/*
				
				If player health > 0 then do:

				- Clears the window
				- Updates Background
				- Spawns Enemies
				- Updates Player Position and UI
				- Displays the Drawn Objects
			*/

			deathSound.stop();
			deathSoundPlayed = false;

			gameoverMusic.stop();
			gameoverMusicPlaying = false;

			pauseMusic.stop();
			pauseMusicPlaying = false;


			// clear the window
			window->clear();

			// Draw background
			background1->Update(*window);
			background2->Update(*window);

			if (menu.lvSelect > 0 && menu.lvSelect <= 3) {

				titlebgMusic.stop();
				titlebgMusicPlaying = false;

				window->setMouseCursorVisible(false);
				// spawn enemies
				SpawnEnemies(players[0]);

				// player position update and shoot
				players[0]->Update(*window, enemylist); // Player Draw

				// player score and health update
				if (menu.lvSelect == 1)
				{
					if (!easybgMusicPlaying) {
						easybgMusic.play();
						easybgMusicPlaying = true;
					}
					players[0]->UI(*window, easyHighScore);
				}
				else if (menu.lvSelect == 2)
				{
					if (!medbgMusicPlaying) {
						medbgMusic.play();
						medbgMusicPlaying = true;
					}
					players[0]->UI(*window, medHighScore);
				}
				else
				{
					if (!hardbgMusicPlaying) {
						hardbgMusic.play();
						hardbgMusicPlaying = true;
					}
					players[0]->UI(*window, hardHighScore);
				}

			}
			else
			{
				if (!titlebgMusicPlaying)
				{
					titlebgMusic.play();
					titlebgMusicPlaying = true;
				}
				window->setMouseCursorVisible(true);
				menu.Update(*window);
				if (menu.resetData)
				{
					easyHighScore = 0;
					medHighScore = 0;
					hardHighScore = 0;
				}
			}

			if (Mouse::isButtonPressed(Mouse::Right)) {
				isGamePaused = true;
			}

			// display
			window->display();
			
			hout.open("High Score.txt");
			hout << easyHighScore << endl << medHighScore << endl << hardHighScore;
			hout.close();

		}
		else if (isGamePaused) {
			pauseScreen();
		}
		else {
			window->setMouseCursorVisible(true);

			/*
				if player health <= 0 then do:

				- Clear the window
				- Draw the fade screen and the gameover text
				- Display the drawn screen
			*/

			if (!deathSoundPlayed) {
				deathSound.play();
				deathSoundPlayed = true;
			}

			if (!gameoverMusicPlaying) {
				gameoverMusic.play();
				gameoverMusicPlaying = true;
			}

			easybgMusic.stop();
			easybgMusicPlaying = false;
			medbgMusic.stop();
			medbgMusicPlaying = false;
			hardbgMusic.stop();
			hardbgMusicPlaying = false;

			for (size_t i = 0; i < enemylist.size(); i++) {
				delete enemylist[i];
				enemylist.erase(enemylist.begin() + i);
			}
			enemies = 0;
			
			players[0]->upgradeCount = 0;
			players[0]->speed = 0.4f;
			players[0]->additionalDamage = 0;

			mousePosWindow = Mouse::getPosition(*window);

			hout << easyHighScore << endl << medHighScore << endl << hardHighScore;
			hout.close();

			// window clear
			window->clear();

			// increasing the transparency of the black screen and gameover text w.r.t time
			static int i = 0;
			Time elapsed = clock1.getElapsedTime();
			if (i < 255 && elapsed >= seconds(0.005)) {
				i++;
				fadeScreen.setFillColor(Color(0, 0, 0, i));
				gameOverSprite.setColor(Color(255, 255, 255, i));
				retrySprite.setColor(Color(255, 255, 255, i));
				btmSprite.setColor(Color(255, 255, 255, i));
				clock1.restart();
			}
			if (!isClicked)
			{
				if (mousePosWindow.x >= retrySprite.getPosition().x + 30.f && mousePosWindow.x <= retrySprite.getPosition().x + 153.f && mousePosWindow.y >= retrySprite.getPosition().y && mousePosWindow.y <= retrySprite.getPosition().y + 33.f) {
					retrySprite.setTexture(retryHoverTexture);
					if (!menu.guiHoverSoundPlayed[7])
					{
						menu.guiHoverSound.stop();
						menu.guiHoverSound.play();
						menu.guiHoverSoundPlayed[7] = true;
					}
					if (Mouse::isButtonPressed(Mouse::Left)) {
						menu.guiSelectSound.stop();
						menu.guiSelectSound.play();
						option = "retry";
						isClicked = true;
					}
				}
				else
				{
					menu.guiHoverSoundPlayed[7] = false;
					retrySprite.setTexture(retryTexture);
				}

				if (mousePosWindow.x >= btmSprite.getPosition().x && mousePosWindow.x + 30.f <= btmSprite.getPosition().x + 306.f && mousePosWindow.y >= btmSprite.getPosition().y && mousePosWindow.y <= btmSprite.getPosition().y + 33.f) {
					btmSprite.setTexture(btmHoverTexture);
					if (!menu.guiHoverSoundPlayed[8])
					{
						menu.guiHoverSound.stop();
						menu.guiHoverSound.play();
						menu.guiHoverSoundPlayed[8] = true;
					}
					if (Mouse::isButtonPressed(Mouse::Left)) {
						menu.guiSelectSound.stop();
						menu.guiSelectSound.play();
						option = "btm";
						isClicked = true;
					}
				}
				else
				{
					menu.guiHoverSoundPlayed[8] = false;
					btmSprite.setTexture(btmTexture);
				}

			}
			else {
				i = 0;
				if (option == "retry")
				{
					if (menu.ClickDelay(retrySprite, retryTexture, isClicked, 8)) {
						option = "";
						players[0]->health = 3;
						players[0]->score = 0;
					}
				}
				else if (option == "btm") {
					if (menu.ClickDelay(btmSprite, btmTexture, isClicked, 8)) {
						option = "";
						players[0]->health = 3;
						players[0]->score = 0;
						menu.lvSelect = 0;
						menu.playClick = false;
					}
				}
				
			}

			// draw black screen and game over text
			window->draw(fadeScreen);
			window->draw(gameOverSprite);
			window->draw(retrySprite);
			window->draw(btmSprite);

			// display
			window->display();

		}
		
	}
}

// Enemy Spawning Function
void Game::SpawnEnemies(Player* player) {

	/*
		- Spawns the enemy after every 1 second interval if:
			- enemies < maxEnemies
		- Puts the enemy spawned in an array of enemies
		- Updates the enemy:
			- Shooting function
		- If enemy is alive:
			- Draw the enemy
		- Otherwise:
			- Delete it
			- and decrement the enemies variable by one
	*/

	// creates a variable "elapsed" to get the time
	Time elapsed = clock1.getElapsedTime();

	// spawning the enemy
	if (elapsed >= seconds(1) && enemies < maxEnemies) {
		enemies++;
		Enemy* enemy;
		if (menu.lvSelect == 1) {
			maxEnemies = 6;
			enemyType = randRange(0, 300);
			enemy = new Enemy(enemyType);
		}
		else if (menu.lvSelect == 2) {
			maxEnemies = 10;
			enemyType = randRange(0, 900);
			if (randRange(0, 100) < 90)
				enemy = new Enemy(enemyType);
			else
				enemy = new EnemyDiagonal(enemyType);
		}
		else {
			maxEnemies = 12;
			enemyType = randRange(0, 2000);
			if (randRange(0, 100) < 70)
				enemy = new Enemy(enemyType);
			else
				enemy = new EnemyDiagonal(enemyType);
		}

		enemylist.push_back(enemy);
		enemy->enemySprite.setPosition(static_cast<float>(randRange(100, 500)), -100);
		clock1.restart();
	}

	// enemy functions
	for (int i = 0; i < enemylist.size(); i++) {
		enemylist[i]->Update();
		if (enemylist[i]->isNormal)
			enemylist[i]->Shoot(*window, players[0]);
		if (!enemylist[i]->Die()) {
			enemylist[i]->enemyUI(*window);
		}
		else {
			Time deadElapsed = enemyDeadClock.getElapsedTime();
			if (!enemylist[i]->isPlayerRewarded)
			{
				enemyDeathSound.stop();
				enemyDeathSound.play();
				enemyDeadClock.restart();
				if (enemylist[i]->type == 1)
					player->score += 10;
				else if (enemylist[i]->type == 2)
					player->score += 20;
				else
					player->score += 30;

				if (player->score >= easyHighScore && menu.lvSelect == 1)
					easyHighScore = player->score;
				if (player->score >= medHighScore && menu.lvSelect == 2)
					medHighScore = player->score;
				if (player->score >= hardHighScore && menu.lvSelect == 3)
					hardHighScore = player->score;
				enemylist[i]->isPlayerRewarded = true;

				if (enemylist[i]->dropChance > enemylist[i]->randomChance && enemylist[i]->dropChance < 100)
				{
					enemylist[i]->upgrade->GetProjectileSprite().setPosition(Vector2f(enemylist[i]->enemySprite.getPosition().x, enemylist[i]->enemySprite.getPosition().y + 33));
					enemylist[i]->upgrade->GetProjectileSprite().setScale(0.15f, 0.15f);
				}

				enemylist[i]->enemyDeadCheck->GetProjectileSprite().setPosition(Vector2f(enemylist[i]->enemySprite.getPosition().x, enemylist[i]->enemySprite.getPosition().y + 33));
				enemylist[i]->enemySprite.setPosition(-1000, -1000);
				enemies--;
				clock1.restart();
			}

			if (enemylist[i]->dropChance > enemylist[i]->randomChance && enemylist[i]->dropChance < 100) {
				if (enemylist[i]->upgrade->collide != true && enemylist[i]->upgrade->GetProjectileSprite().getPosition().y <= 800 && enemylist[i]->upgrade->GetProjectileSprite().getPosition().x > 0) {
					window->draw(enemylist[i]->upgrade->GetProjectileSprite());
					enemylist[i]->upgrade->Update();
					enemylist[i]->upgrade->Colliding(player, enemylist[i]->upgrade);
				}
				else if (enemylist[i]->upgrade->collide || enemylist[i]->upgrade->GetProjectileSprite().getPosition().y >= 800 || enemylist[i]->upgrade->GetProjectileSprite().getPosition().x == 0) {
					enemylist[i]->upgrade->GetProjectileSprite().setPosition(-1000, -1000);
				}
			}

			static int j = 255;
			if (enemylist[i]->enemyDeadCheck->GetProjectileSprite().getPosition().y <= 800 && enemylist[i]->enemyDeadCheck->GetProjectileSprite().getPosition().x > 0) {
				window->draw(enemylist[i]->enemyDeadCheck->GetProjectileSprite());
				enemylist[i]->enemyDeadCheck->Update();
				enemylist[i]->enemyDeadCheck->blinkDeadCheck(*enemylist[i]);
			}
			else if (enemylist[i]->enemyDeadCheck->GetProjectileSprite().getPosition().y >= 800) {
				delete enemylist[i]->enemyDeadCheck;
				delete enemylist[i];
				enemylist.erase(enemylist.begin() + i);
			}

		}
	}
	
}

// Random number selector from low to high
int Game::randRange(int low, int high)
{
	return rand() % (high - low) + low;
}

void Game::pauseScreen()
{
	window->setMouseCursorVisible(true);

	/*
		if player health <= 0 then do:

		- Clear the window
		- Draw the fade screen and the gameover text
		- Display the drawn screen
	*/

	if (!pauseMusicPlaying) {
		pauseMusic.play();
		pauseMusicPlaying = true;
	}

	easybgMusic.stop();
	easybgMusicPlaying = false;
	medbgMusic.stop();
	medbgMusicPlaying = false;
	hardbgMusic.stop();
	hardbgMusicPlaying = false;

	mousePosWindow = Mouse::getPosition(*window);

	// window clear
	window->clear();

	// increasing the transparency of the black screen and gameover text w.r.t time
	static int i = 0;
	Time elapsed = clock1.getElapsedTime();
	if (!isClicked)
	{
		if (mousePosWindow.x >= resumeSprite.getPosition().x + 30.f && mousePosWindow.x <= resumeSprite.getPosition().x + 153.f && mousePosWindow.y >= resumeSprite.getPosition().y && mousePosWindow.y <= resumeSprite.getPosition().y + 33.f) {
			resumeSprite.setTexture(resumeHoverTexture);
			if (!menu.guiHoverSoundPlayed[9])
			{
				menu.guiHoverSound.stop();
				menu.guiHoverSound.play();
				menu.guiHoverSoundPlayed[9] = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left)) {
				menu.guiSelectSound.stop();
				menu.guiSelectSound.play();
				option = "resume";
				isClicked = true;
			}
		}
		else
		{
			menu.guiHoverSoundPlayed[9] = false;
			resumeSprite.setTexture(resumeTexture);
		}

		if (mousePosWindow.x >= btmSprite.getPosition().x && mousePosWindow.x + 30.f <= btmSprite.getPosition().x + 306.f && mousePosWindow.y >= btmSprite.getPosition().y && mousePosWindow.y <= btmSprite.getPosition().y + 33.f) {
			btmSprite.setTexture(btmHoverTexture);
			if (!menu.guiHoverSoundPlayed[8])
			{
				menu.guiHoverSound.stop();
				menu.guiHoverSound.play();
				menu.guiHoverSoundPlayed[8] = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left)) {
				menu.guiSelectSound.stop();
				menu.guiSelectSound.play();
				option = "btm";
				isClicked = true;
			}
		}
		else
		{
			menu.guiHoverSoundPlayed[8] = false;
			btmSprite.setTexture(btmTexture);
		}

	}
	else {
		if (option == "btm") {
			for (size_t i = 0; i < enemylist.size(); i++) {
				delete enemylist[i];
				enemylist.erase(enemylist.begin() + i);
			}
			enemies = 0;
			players[0]->upgradeCount = 0;
			players[0]->speed = 0.4f;
			players[0]->additionalDamage = 0;
			players[0]->health = 3;
			players[0]->score = 0;
			if (menu.ClickDelay(btmSprite, btmTexture, isClicked, 8)) {
				option = "";
				menu.lvSelect = 0;
				menu.playClick = false;
				isGamePaused = false;
			}
		}
		else if (option == "resume") {
			if (menu.ClickDelay(resumeSprite, resumeTexture, isClicked, 10)) {
				option = "";
				isGamePaused = false;
			}
		}
	}
	// draw black screen and game over text
	window->draw(pauseSprite);
	window->draw(resumeSprite);
	window->draw(btmSprite);

	// display
	window->display();
}

// Destructor
Game::~Game() {  // TO SAVE MEMORY
	delete background1;
	delete background2;
	delete window;
	for (size_t i = 0; i < enemylist.size(); i++) {
		delete enemylist[i];
		enemylist.erase(enemylist.begin() + i);
	}
}

