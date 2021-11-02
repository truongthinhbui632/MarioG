#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "MushRoom.h"

class QuestionBrick : public Sprite
{
public:

	enum BrickType { CoinType, MushRoomType, WingType };

private:
	Texture* objectsTexture;

	Animation brickAnimation;
	Animation brickAnimationStatic;

	Body* body;

	World* world;

	bool isAlreadyHit;

	BrickType brickType;

	MushRoom mushRoom;

public:

	QuestionBrick();
	~QuestionBrick();
	void Create(World* world, Texture* brickTexture, BrickType brickType, float x, float y);

	void Render(SpriteBatch* batch);

	void Update(float dt);

	void OnBeingHit();
};
