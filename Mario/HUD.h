#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"

class HUD
{
private:
	
	std::vector<Sprite> powerHolders;
	std::vector <Sprite> powerHolderFillers;

	int power = 0;

public:

	void Create(Texture* objectTexture, float x, float y);
	void UpdatePosition(float x, float y);
	void UpdatePowerFiller(int power);
	void Render(SpriteBatch *batch);
};