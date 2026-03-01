#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include "Timer.h"

using namespace std;
using namespace sf;

class Menu
{
private:

	Text highScore, areYouSure;
	Vector2i mousePosWindow;
	Clock clock;

	Texture bgTexture;
	Sprite bgSprite;

	Texture titleTexture;
	Sprite titleSprite;

	Texture playTexture, resetTexture, quitTexture;
	Texture playHoverTexture, resetHoverTexture, quitHoverTexture;
	Sprite playSprite, resetSprite, quitSprite;

	Texture easyTexture, medTexture, hardTexture, backTexture;
	Texture easyHoverTexture, medHoverTexture, hardHoverTexture, backHoverTexture;
	Sprite easySprite, medSprite, hardSprite, backSprite;

	Texture easyInfoTexture, medInfoTexture, hardInfoTexture;
	Sprite easyInfoSprite, medInfoSprite, hardInfoSprite;

	int delayCount = 0;
	int spriteTrans = 255;
	string option = "";

	int easyScore = 0, medScore = 0, hardScore = 0;

public:

	Font font;

	Menu();
	~Menu();

	int lvSelect = 0;
	bool isClicked = false;
	bool playClick = false;
	bool resetData = false;
	bool AREYOUSURE = false;
	bool moveDown = true;

	SoundBuffer guiHoverBuffer, guiSelectBuffer;
	Sound guiHoverSound, guiSelectSound;
	bool guiHoverSoundPlayed[10];

	void Hover(RenderWindow& window);
	void Hover2(RenderWindow& window);
	bool ClickDelay(Sprite& sprite, Texture& texture, bool& clicked, int delay);
	void titleMove();
	void Update(RenderWindow& window);

};

