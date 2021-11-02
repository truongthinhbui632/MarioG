#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

class Goomba : public Sprite
{

private:
	Animation goombaAnimation;

	Body* body;

	World* world;

	bool isDead;
	float velocityX;
public:
	Goomba();
	~Goomba();
	void Create(World* world, Texture* goombaTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitOnTheHead();

	void ChangeDirection();

	bool IsDead();
};
