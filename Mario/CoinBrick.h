#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"

class CoinBrick : public Sprite
{
private:
	Texture* objectsTexture;

	Animation coinBrickAnimation;
	Animation normalCoinAnimation;

	Body* bodyBrick;
	Body* bodyCoin;
	World* world;

	bool isCoin;

public:

	CoinBrick();
	~CoinBrick();
	void Create(World* world, Texture* brickTexture, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	bool IsCoin();

	void TurnToCoin();

	void TurnBackToBrick();

	void Destroy();
};
