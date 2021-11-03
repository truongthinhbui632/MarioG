#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

#define KOOPAINVINCIBLETIME 0.2f

class Koopa : public Sprite
{

private:
	Animation koopaMovingAnimation;
	Animation koopaStaticAnimation;
	Animation koopaRollingAnimation;

	Body* body;

	World* world;

	int health;

	bool isDead;

	float invincibleTime;
	float velocityX;

public:
	Koopa();
	~Koopa();
	void Create(World* world, Texture* goombaTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitOnTheHead();

	void ChangeDirection();

	bool IsDead();
};
