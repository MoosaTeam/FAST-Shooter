#pragma once

#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Background {
private:
	const int noOfImg = 3;
	Sprite backgroundSprite[3];
	Texture backgroundTexture[3];
	string bgNames[3] = { "Sprite/sky.png", "Sprite/small_stars.png", "Sprite/mid_stars.png" };

public:
	// constructor / destructor
	Background(int y);
	~Background();

	void Update(RenderWindow& window);
	void LoopBackground();
	void SetSpriteTexture(int y);

};