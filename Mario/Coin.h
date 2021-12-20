#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

class Coin : public Sprite
{
private:
	Texture* objectsTexture;

	Animation coinAnimation;

	Body* body;
	World* world;

public:

	Coin();
	~Coin();
	void Create(World* world, Texture* brickTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void Destroy();
};
