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

	World* world;

	int health;

	bool isInShell;

	float invincibleTime;

	float shellTime;

	float flickeringTime;

public:
	Koopa();
	~Koopa();

	Body* body;
	float velocityX;

	void Create(World* world, Texture* goombaTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitOnTheHead(bool right);

	void ChangeDirection();

	bool IsInShell();
};
