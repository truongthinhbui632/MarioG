#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{

}


void Player::Create(World* world, float x, float y)
{
	isDead = false;
	isBig = false;
	isRacoon = false;
	isGrounded = true;
	jumpTime = 0;

	//get characterTexture
	texture = Texture("Resources/mario.png");
	TexturePacker p = TexturePacker(&texture, "Resources/mario_packer.xml");

	//Set size & position
	SetRegion(p.GetRegion("running").at(0));
	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//get animations
	standingAnimation.AddRegion(p.GetRegion("standing"));
	movingAnimation.AddRegion(p.GetRegion("running"));
	movingAnimation.SetFrameInterval(0.02);
	bigStandingAnimation.AddRegion(p.GetRegion("bigstanding"));
	bigMovingAnimation.AddRegion(p.GetRegion("bigrunning"));
	bigMovingAnimation.SetFrameInterval(0.02);
	racoonStandingAnimation.AddRegion(p.GetRegion("racoonstanding"));
	racoonMovingAnimation.AddRegion(p.GetRegion("racoonrunning"));
	racoonFlyingAnimation.AddRegion(p.GetRegion("racoonflying"));

	//setup mainbody
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.linearDrag.Set(10, 1);
	bodyDef.mass = 2;
	bodyDef.size.Set(16 * 1.5, 16 * 1.5);
	bodyDef.position.Set(x, y);
	mainBody = world->CreateBody(bodyDef);
	mainBody->categoryBits = PLAYER_BIT;
	mainBody->maskBits = PLATFORM_BIT | GOOMBA_BIT | WINGGOOMBA_BIT | QUESTIONBRICK_BIT | MUSHROOM_BIT | KOOPA_BIT | COIN_BIT | COINBRICK_BIT | LEAF_BIT;
	mainBody->PutExtra(this);

	//create foot
	BodyDef footDef;
	footDef.bodyType = Body::BodyType::Kinematic;
	footDef.size.Set(16 * 1.49, 16 * 1.49);
	footDef.isSensor = true;
	foot = world->CreateBody(footDef);
	foot->categoryBits = FOOT_BIT;
	foot->maskBits = PLATFORM_BIT | GOOMBA_BIT | WINGGOOMBA_BIT | QUESTIONBRICK_BIT | KOOPA_BIT | COINBRICK_BIT;
	foot->PutExtra(this);

	//create head
	BodyDef headDef;
	headDef.bodyType = Body::BodyType::Kinematic;
	headDef.size.Set(16 * 1.49, 16 * 1.49);
	headDef.isSensor = true;
	head = world->CreateBody(headDef);
	head->categoryBits = HEAD_BIT;
	head->maskBits =  QUESTIONBRICK_BIT;
	head->PutExtra(this);
}


void Player::HandleInput()
{
	if (isDead) return;

	//Move right
	if (Input::GetKey(DIK_RIGHT))
	{
		mainBody->SetVelocity(7, mainBody->GetVelocity().y);
	}

	//move left
	if (Input::GetKey(DIK_LEFT))
	{
		mainBody->SetVelocity(-7, mainBody->GetVelocity().y);
	}

	////hold-jump 
	//if (Input::GetKey(DIK_Z))
	//{
	//	if (jumpTime < MAXJUMPTIME) //continue jumping if there is still jumptime
	//	{
	//		mainBody->SetVelocity(mainBody->GetVelocity().x, mainBody->GetVelocity().y + 0.5f);
	//		jumpTime += 0.02f;
	//	}
	//	else
	//	{
	//		jumpTime = 100;  //don't jump more
	//	}
	//}
	//else
	//{
	//	jumpTime = 100; //don't jump more
	//}

	//jump only if grounded
	if (Input::GetKeyDown(DIK_UP) && isGrounded)
	{
		mainBody->SetVelocity(mainBody->GetVelocity().x, 10);
		isGrounded = false;
		jumpTime = 0;
	}

	if (Input::GetKey(DIK_UP) && isRacoon)
	{
		mainBody->SetVelocity(mainBody->GetVelocity().x, 3);
	}
}

void Player::Render(SpriteBatch *batch)
{	
	if (isDead) return;

	//draw player
	batch->Draw(*this);
}


void Player::Update(float dt)
{
	if (isDead) return;

	//flip if necessary
	if (mainBody->GetVelocity().x > 0)
	{
		this->Flip(false, false);
	}
	else
	{
		if (mainBody->GetVelocity().x < 0)
		{
			this->Flip(true, false);
		}
	}

	//Animations
	if (isGrounded)
	{
		if (mainBody->GetVelocity().x != 0)
		{
			if (isRacoon)
			{
				SetRegion(*racoonMovingAnimation.Next(dt));
			}
			else
			{
				if (isBig)
				{
					SetRegion(*bigMovingAnimation.Next(dt));
				}
				else
				{
					SetRegion(*movingAnimation.Next(dt));
				}
			}
		}
		else
		{
			if (isRacoon)
			{
				SetRegion(*racoonStandingAnimation.Next(dt));
			}
			else
			{
				if (isBig)
				{
					SetRegion(*bigStandingAnimation.Next(dt));
				}
				else
				{
					SetRegion(*standingAnimation.Next(dt));
				}
			}
		}
	}
	else
	{
		if (isRacoon)
		{
			SetRegion(*racoonFlyingAnimation.Next(dt));
		}
		else
		{
			if (isBig)
			{
				SetRegion(*bigStandingAnimation.Next(dt));
			}
			else
			{
				SetRegion(*standingAnimation.Next(dt));
			}
		}
	}

	if (invincibleTime > 0)
	{
		invincibleTime -= dt;
		flickeringTime -= dt;
		if (flickeringTime < 0)
		{
			SetRegion(TextureRegion());
			flickeringTime = 0.05f;
		}
	}

	//update sprite position
	SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);
	if (isBig || isRacoon)
	{
		foot->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y - 26);
		head->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y + 26);
	}
	else
	{
		foot->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y - 15);
		head->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y + 15);
	}
}

void Player::DamagePlayer()
{
	if (invincibleTime > 0) return;

	if (isRacoon)
	{
		isBig = true;
		isRacoon = false;
		invincibleTime = PLAYERINVINCIBLETIME;
		flickeringTime = 0.05f;
		return;
	}

	if (isBig)
	{
		isBig = false;
		mainBody->SetSize(16 * 1.5f, 16 * 1.5f);
		invincibleTime = PLAYERINVINCIBLETIME;
		flickeringTime = 0.05f;
	}
	else
	{
		isDead = true;
		mainBody->maskBits = 0;
		foot->maskBits = 0;
	}
}

void Player::OnGrounded()
{
	isGrounded = true;
	jumpTime = 100;
}

void Player::OnExitGround()
{
	isGrounded = false;
	jumpTime = 0;
}

void Player::JumpWhenKillEnemies()
{
	mainBody->SetVelocity(mainBody->GetVelocity().x, 8);
	OnExitGround();
}

void Player::BecomeBig()
{
	isBig = true;
	mainBody->SetSize(16 * 1.5f, 27 * 1.5f);
}

void Player::BecomRacoon()
{
	isRacoon = true;
	mainBody->SetSize(16 * 1.5f, 27 * 1.5f);
}

void Player::Release()
{

}
