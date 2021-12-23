#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

class Leaf : public Sprite
{

private:
	Animation leafAnimation;

	Body* body;

	World* world;

	float timeToChangeDirection;

	float timeToStop;

	float speed;

	bool isEaten;
public:
	Leaf();
	~Leaf();
	void Create(World* world, Texture* leafTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitPlayer();
};
