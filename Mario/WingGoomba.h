#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

#define WINGMUSHROOMTIMEBETWEENJUMP 1.5f
#define WINGMUSHROOMINVINCIBLETIME 0.2f

class WingGoomba : public Sprite
{

private:
	Animation wingGoombaAnimation1;
	Animation wingGoombaAnimation2;

	Body* body;

	World* world;

	int health;

	bool isDead;

	float timeBetweenJump;
	float invincibleTime;
	float velocityX;

public:
	WingGoomba();
	~WingGoomba();
	void Create(World* world, Texture* goombaTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitOnTheHead();

	void ChangeDirection();

	bool IsDead();
};
