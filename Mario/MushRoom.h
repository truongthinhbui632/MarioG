#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

class MushRoom : public Sprite
{

private:
	Animation mushroomAnimation;

	Body* body;

	World* world;

	bool isEaten;
public:
	MushRoom();
	~MushRoom();
	void Create(World* world, Texture* mushroomTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitPlayer();
};
