#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "Player.h"

class MushRoom : public Sprite
{

private:
	Animation mushroomAnimation;

	Body* body;

	World* world;

	bool isDead;

public:
	MushRoom();
	~MushRoom();
	void Create(World* world, Texture* mushRoomTexture, int x, int y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnHitOnTheHead();

	void ChangeDirection();

	bool IsDead();
};
