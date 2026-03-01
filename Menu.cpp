#include "Menu.h"

Menu::Menu()
{
	if (!font.loadFromFile("Fonts/ThaleahFat.ttf")) {}
	highScore.setFont(font);
	highScore.setCharacterSize(30);
	highScore.setFillColor(Color::White);
	highScore.setPosition(50, 720);

	areYouSure.setFont(font);
	areYouSure.setCharacterSize(20);
	areYouSure.setFillColor(Color::White);
	areYouSure.setPosition(75, 750);
	areYouSure.setString("ARE YOU SURE? (ClICK RIGHT MOUSE BUTTON TO CONFIRM)");

	if (!easyInfoTexture.loadFromFile("Sprite/GUI_Easy_instructions.png")) {}
	if (!medInfoTexture.loadFromFile("Sprite/GUI_Medium_instructions.png")) {}
	if (!hardInfoTexture.loadFromFile("Sprite/GUI_Hard_instructions.png")) {}

	easyInfoSprite.setTexture(easyInfoTexture);
	medInfoSprite.setTexture(medInfoTexture);
	hardInfoSprite.setTexture(hardInfoTexture);

	easyInfoSprite.setScale(3.f, 3.f);
	medInfoSprite.setScale(3.f, 3.f);
	hardInfoSprite.setScale(3.f, 3.f);

	easyInfoSprite.setPosition(0.f, 0.f);
	medInfoSprite.setPosition(0.f, 0.f);
	hardInfoSprite.setPosition(0.f, 0.f);

	if (!titleTexture.loadFromFile("Sprite/FAST_Shooter_Logo.png")) {}

	titleSprite.setTexture(titleTexture);
	titleSprite.setOrigin(Vector2f(titleSprite.getTexture()->getSize().x * 0.5, titleSprite.getTexture()->getSize().y * 0.5));
	titleSprite.setScale(0.3f, 0.3f);
	titleSprite.setPosition(300.f, 200.f);

	if (!bgTexture.loadFromFile("Sprite/title screen.png")) {}
	bgSprite.setTexture(bgTexture);

	if (!playTexture.loadFromFile("Sprite/(GUI) PLAY (UNCLICKED).png")) {}
	if (!playHoverTexture.loadFromFile("Sprite/(GUI) PLAY (HOVER).png")) {}

	if (!resetTexture.loadFromFile("Sprite/(GUI) RESET (UNCLICKED).png")) {}
	if (!resetHoverTexture.loadFromFile("Sprite/(GUI) RESET (HOVER.png")) {}

	if (!quitTexture.loadFromFile("Sprite/(GUI) QUIT (UNCLICKED).png")) {}
	if (!quitHoverTexture.loadFromFile("Sprite/(GUI) QUIT (HOVER).png")) {}

	playSprite.setTexture(playTexture);
	resetSprite.setTexture(resetTexture);
	quitSprite.setTexture(quitTexture);

	playSprite.setScale(3.f, 3.f);
	resetSprite.setScale(3.f, 3.f);
	quitSprite.setScale(3.f, 3.f);

	playSprite.setPosition(Vector2f(217.5f, 440.f));
	resetSprite.setPosition(Vector2f(153.f, 500.f));
	quitSprite.setPosition(Vector2f(171.f, 560.f));

	if (!easyTexture.loadFromFile("Sprite/(GUI) EASY (UNCLICKED).png")) {}
	if (!easyHoverTexture.loadFromFile("Sprite/(GUI) EASY (HOVER).png")) {}

	if (!medTexture.loadFromFile("Sprite/(GUI) MEDIUM (UNCLICKED).png")) {}
	if (!medHoverTexture.loadFromFile("Sprite/(GUI) MEDIUM (HOVER).png")) {}

	if (!hardTexture.loadFromFile("Sprite/(GUI) HARD (UNCLICKED).png")) {}
	if (!hardHoverTexture.loadFromFile("Sprite/(GUI) HARD (HOVER).png")) {}

	if (!backTexture.loadFromFile("Sprite/(GUI) BACK (UNCLICKED).png")) {}
	if (!backHoverTexture.loadFromFile("Sprite/(GUI) BACK (HOVER).png")) {}

	easySprite.setTexture(easyTexture);
	medSprite.setTexture(medTexture);
	hardSprite.setTexture(hardTexture);
	backSprite.setTexture(backTexture);

	easySprite.setScale(3.f, 3.f);
	medSprite.setScale(3.f, 3.f);
	hardSprite.setScale(3.f, 3.f);
	backSprite.setScale(3.f, 3.f);

	easySprite.setPosition(Vector2f(219.f, 100.f));
	medSprite.setPosition(Vector2f(201.f, 160.f));
	hardSprite.setPosition(Vector2f(217.5f, 220.f));
	backSprite.setPosition(Vector2f(217.5f, 280.f));

	if (!guiHoverBuffer.loadFromFile("Sounds/GUI hover.wav")) {}
	guiHoverSound.setBuffer(guiHoverBuffer);
	guiHoverSound.setVolume(10.f);

	if (!guiSelectBuffer.loadFromFile("Sounds/GUI select.wav")) {}
	guiSelectSound.setBuffer(guiSelectBuffer);
	guiSelectSound.setVolume(10.f);

	for (int i = 0; i < 10; i++) {
		guiHoverSoundPlayed[i] = false;
	}

}

void Menu::Hover(RenderWindow& window) {
	mousePosWindow = Mouse::getPosition(window);
	if (!isClicked)
	{
		if (mousePosWindow.x >= playSprite.getPosition().x + 30.f && mousePosWindow.x <= playSprite.getPosition().x + 135.f && mousePosWindow.y >= playSprite.getPosition().y && mousePosWindow.y <= playSprite.getPosition().y + 33.f) {
			playSprite.setTexture(playHoverTexture);
			if (!guiHoverSoundPlayed[0])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[0] = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				option = "play";
				isClicked = true;
			}

		}
		else
		{
			guiHoverSoundPlayed[0] = false;
			playSprite.setTexture(playTexture);
		}

		if (mousePosWindow.x >= resetSprite.getPosition().x + 30.f && mousePosWindow.x <= resetSprite.getPosition().x + 264.f && mousePosWindow.y >= resetSprite.getPosition().y && mousePosWindow.y <= resetSprite.getPosition().y + 33.f) {
			resetSprite.setTexture(resetHoverTexture);
			if (!guiHoverSoundPlayed[1])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[1] = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				option = "reset";
				isClicked = true;
			}

		}
		else
		{
			guiHoverSoundPlayed[1] = false;
			resetSprite.setTexture(resetTexture);
		}

		if (mousePosWindow.x >= quitSprite.getPosition().x + 30.f && mousePosWindow.x <= quitSprite.getPosition().x + 228.f && mousePosWindow.y >= quitSprite.getPosition().y && mousePosWindow.y <= quitSprite.getPosition().y + 33.f) {
			quitSprite.setTexture(quitHoverTexture);
			if (!guiHoverSoundPlayed[2])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[2] = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				option = "quit";
				isClicked = true;
			}
		}
		else
		{
			guiHoverSoundPlayed[2] = false;
			quitSprite.setTexture(quitTexture);
		}

	}
	else {
		if (option == "play") {
			if (ClickDelay(playSprite, playTexture, isClicked, 10)) {
				option = "";
				playClick = true;
			}
		}
		else if (option == "reset") {
			window.draw(areYouSure);
			if (ClickDelay(resetSprite, resetTexture, isClicked, 50) || !isClicked)
			{	
				resetData = false;
				option = "";
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				guiSelectSound.stop();
				guiSelectSound.play();
				isClicked = false;
				resetData = true;
				resetSprite.setColor(Color(255, 255, 255, 255));
			}
			
		}
		else if (option == "quit") {
			if (ClickDelay(quitSprite, quitTexture, isClicked, 10))
			{
				ofstream hOUT("High Score.txt");
				hOUT << easyScore << '\n' << medScore << '\n' << hardScore;
				hOUT.close();
				option = "";
				window.close();
			}
		}
	}
}

void Menu::Hover2(RenderWindow& window)
{
	mousePosWindow = Mouse::getPosition(window);
	ifstream hn("High Score.txt");
	hn >> easyScore >> medScore >> hardScore;
	hn.close();
	if (!isClicked)
	{
		if (mousePosWindow.x >= easySprite.getPosition().x + 30.f && mousePosWindow.x <= easySprite.getPosition().x + 132.f && mousePosWindow.y >= easySprite.getPosition().y && mousePosWindow.y <= easySprite.getPosition().y + 33.f) {
			easySprite.setTexture(easyHoverTexture);
			if (!guiHoverSoundPlayed[3])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[3] = true;
			}
			highScore.setString("High Score: " + to_string(easyScore));
			window.draw(highScore);
			window.draw(easyInfoSprite);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				lvSelect = 10;
				isClicked = true;
			}

		}
		else
		{
			guiHoverSoundPlayed[3] = false;
			easySprite.setTexture(easyTexture);
		}

		if (mousePosWindow.x >= medSprite.getPosition().x + 30.f && mousePosWindow.x <= medSprite.getPosition().x + 168.f && mousePosWindow.y >= medSprite.getPosition().y && mousePosWindow.y <= medSprite.getPosition().y + 33.f) {
			medSprite.setTexture(medHoverTexture);
			if (!guiHoverSoundPlayed[4])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[4] = true;
			}
			highScore.setString("High Score: " + to_string(medScore));
			window.draw(highScore);
			window.draw(medInfoSprite);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				lvSelect = 20;
				isClicked = true;
			}

		}
		else
		{
			guiHoverSoundPlayed[4] = false;
			medSprite.setTexture(medTexture);
		}

		if (mousePosWindow.x >= hardSprite.getPosition().x + 30.f && mousePosWindow.x <= hardSprite.getPosition().x + 135.f && mousePosWindow.y >= hardSprite.getPosition().y && mousePosWindow.y <= hardSprite.getPosition().y + 33.f) {
			hardSprite.setTexture(hardHoverTexture);
			if (!guiHoverSoundPlayed[5])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[5] = true;
			}
			highScore.setString("High Score: " + to_string(hardScore));
			window.draw(highScore);
			window.draw(hardInfoSprite);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				lvSelect = 30;
				isClicked = true;
			}
		}
		else
		{
			guiHoverSoundPlayed[5] = false;
			hardSprite.setTexture(hardTexture);
		}

		if (mousePosWindow.x >= backSprite.getPosition().x + 30.f && mousePosWindow.x <= backSprite.getPosition().x + 135.f && mousePosWindow.y >= backSprite.getPosition().y && mousePosWindow.y <= backSprite.getPosition().y + 33.f) {
			backSprite.setTexture(backHoverTexture);
			if (!guiHoverSoundPlayed[6])
			{
				guiHoverSound.stop();
				guiHoverSound.play();
				guiHoverSoundPlayed[6] = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				guiSelectSound.stop();
				guiSelectSound.play();
				isClicked = true;
			}
		}
		else
		{
			guiHoverSoundPlayed[6] = false;
			backSprite.setTexture(backTexture);
		}
		
	}
	else {
		if (lvSelect == 10)
		{
			if (ClickDelay(easySprite, easyTexture, isClicked, 14))
				lvSelect /= 10;
		}
		else if (lvSelect == 20)
		{
			if (ClickDelay(medSprite, medTexture, isClicked, 14))
				lvSelect /= 10;
		}
		else if (lvSelect == 30)
		{
			if (ClickDelay(hardSprite, hardTexture, isClicked, 14))
				lvSelect /= 10;
		}
		else {
			if (ClickDelay(backSprite, backTexture, isClicked, 10))
				playClick = false;
		}
	}

}

bool Menu::ClickDelay(Sprite& sprite, Texture& texture, bool& clicked, int delay) {
	
	if (delayCount < delay) {
		sprite.setTexture(texture);
		if (delayCount % 2 != 0) {
			spriteTrans += 3000 * timesec::deltaTime;
			if (spriteTrans >= 255) {
				spriteTrans = 255;
				delayCount++;
			}
			sprite.setColor(Color(255, 255, 255, 255));
		}
		else {
			spriteTrans -= 3000 * timesec::deltaTime;
			if (spriteTrans <= 50) {
				spriteTrans = 50;
				delayCount++;
			}
			sprite.setColor(Color(255, 255, 255, 0));
		}
		return false;
	}
	else 
	{
		delayCount = 0;
		clicked = false;
		return true;
	}
}

void Menu::titleMove() {
	if (titleSprite.getPosition().y <= 220.f && !moveDown)
	{
		titleSprite.move(0, -0.025);
		if (titleSprite.getPosition().y <= 190.f)
			moveDown = true;
	}
	else if (titleSprite.getPosition().y >= 180.f && moveDown)
	{
		titleSprite.move(0, 0.025);
		if (titleSprite.getPosition().y >= 210.f)
			moveDown = false;
	}
}

void Menu::Update(RenderWindow& window)
{
	window.draw(bgSprite);
	if (!playClick) {
		titleMove();
		window.draw(titleSprite);
		Hover(window);
		window.draw(playSprite);
		window.draw(resetSprite);
		window.draw(quitSprite);
	} 
	else {
		Hover2(window);
		window.draw(easySprite);
		window.draw(medSprite);
		window.draw(hardSprite);
		window.draw(backSprite);
	}
}

Menu::~Menu()
{


}




