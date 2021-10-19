#pragma once
#include "HanabiSprite.h"
#include "HanabiInput.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"
#include "HanabiConsole.h"

#define MAXJUMPTIME 0.4

//Main character
class Player : public Sprite
{
private:
	Texture texture;

	//Body
	Body* mainBody;
	Body* foot;
	Body* head;

	//Animations
	Animation standingAnimation;
	Animation movingAnimation;

	bool isDead;

	float jumpTime;
	bool isGrounded;

public:
	Player();
	~Player();

	void Create(World* world, float x, float y);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void DamagePlayer();

	void OnExitGround();
	void OnGrounded();

	void JumpWhenKillEnemies();

	void Release();
};

