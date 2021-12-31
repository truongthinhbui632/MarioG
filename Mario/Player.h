#pragma once
#include "HanabiSprite.h"
#include "HanabiInput.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"
#include "HanabiConsole.h"
#include "Koopa.h"

#define PLAYERINVINCIBLETIME 0.5
#define XMINVELOCITY 5
#define XMAXVELOCITY 7
#define YFLYINGMAXVELOCITY 3
#define YFLYINGMINVELOCITY 2
#define MAXPOWER 5

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
	Animation jumpingAnimation;
	Animation carryingAnimation;
	Animation carryingRunningAnimation;
	Animation bigStandingAnimation;
	Animation bigMovingAnimation;
	Animation bigJumpingAnimation;
	Animation bigCarryingAnimation;
	Animation bigCarryingRunningAnimation;
	Animation racoonStandingAnimation;
	Animation racoonMovingAnimation;
	Animation racoonFlyingAnimation;
	Animation racoonTailAtkAnimation;
	Animation racoonCarryingAnimation;
	Animation racoonCarryingRunningAnimation;
	Animation marioDeadAnimation;

	bool isBig;
	bool isRacoon;
	
	bool isDead;
	bool isTailAtk;

	float timeToDie;
	float jumpTime;
	float power = 0;
	float xVelocity;
	float yVelocity;
	float invincibleTime;
	float flickeringTime;
	bool isGrounded;

	Koopa* koopa;

public:
	Player();
	~Player();

	bool isOnPortal;

	void Create(World* world, float x, float y);

	void SetBodyPosition(float x, float y);

	void HandleInput(float dt);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void DamagePlayer(bool kill = false);

	void OnExitGround();
	void OnGrounded();

	void JumpWhenKillEnemies();

	void BecomeBig();

	void BecomRacoon();

	void SetOnPortal(bool onPortal);

	int GetPower();

	bool IsDead();

	bool TailAtk();

	void PickUpKoopa(Koopa *koopa);

	void UpdatePower(float dt);

	void Release();
};

