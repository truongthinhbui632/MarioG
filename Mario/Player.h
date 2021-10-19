#pragma once
#include "HanabiSprite.h"
#include "HanabiInput.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"

#define MAXJUMPTIME 0.4

//Main character
class Player : public Sprite
{
private:
	Texture texture;

	//Body
	Body* mainBody;

	//Animations
	Animation standingAnimation;
	Animation movingAnimation;

	float jumpTime;
	bool isGrounded;

public:
	Player();
	~Player();

	void Create(World* world, float x, float y);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void Release();
};

