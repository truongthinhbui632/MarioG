#pragma once
#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

class Portal : public Sprite
{

private:
	Body* body;

	World* world;
public:
	Portal();
	~Portal();
	void Create(World* world, Texture* leafTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);
};
