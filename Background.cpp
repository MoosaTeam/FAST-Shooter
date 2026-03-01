#include "Background.h"
#include<SFML/Window.hpp>

// constructor
Background::Background(int y) {
	// creates and sets background
	SetSpriteTexture(y);
}

// sets the texture and sprite
void Background::SetSpriteTexture(int y) {
	
	for (int i = 0; i < noOfImg; i++)
	{
		backgroundSprite[i].setPosition(0, y);
		backgroundSprite[i].setScale(2, 2);
		if (!backgroundTexture[i].loadFromFile(bgNames[i])) {}
		backgroundTexture[i].setSmooth(true);
		backgroundSprite[i].setTexture(backgroundTexture[i]);
	}
}

// loops background
void Background::LoopBackground() {
	for (int i = 0; i < noOfImg; i++)
	{
		if (backgroundSprite[i].getPosition().y >= 800) {
			backgroundSprite[i].setPosition(0, -800);
		}
	}
}

// updates bg
void Background::Update(RenderWindow& window) {
	LoopBackground();
	for (int i = 0; i < noOfImg; i++) {
		backgroundSprite[i].move(Vector2f(0, i * 0.1));
		window.draw(backgroundSprite[i]);
	}
	
}

Background::~Background() {

}