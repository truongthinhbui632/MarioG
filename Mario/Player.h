#pragma once
#include "HanabiSprite.h"
#include "HanabiInput.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"
#include "HanabiConsole.h"

#define PLAYERINVINCIBLETIME 0.5

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
	Animation bigStandingAnimation;
	Animation bigMovingAnimation;
	Animation racoonStandingAnimation;
	Animation racoonMovingAnimation;
	Animation racoonFlyingAnimation;

	bool isBig;
	bool isRacoon;
	
	bool isDead;

	float jumpTime;
	float power;
	float invincibleTime;
	float flickeringTime;
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

	void BecomeBig();

	void BecomRacoon();

	void Release();
};

