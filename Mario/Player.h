#pragma once
#include "HanabiSprite.h"
#include <vector>
#include "HanabiInput.h"
#define FIRERATE 0.1
#define MAXJUMPTIME 0.4
#define MAXUNTOUCHABLETIME 0.3 
#define MAXDEADTIME 0.5

//Main character
class Player : public Sprite
{
private:
	Texture texture;

public:
	Player();
	~Player();

	void Create(float x, float y);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);
};

