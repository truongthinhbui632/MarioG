#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{

}


void Player::Create(World* world, float x, float y)
{
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

	//setup mainbody
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.linearDrag.Set(10, 1);
	bodyDef.mass = 2;
	bodyDef.size.Set(16 * 1.5, 16 * 1.5);
	bodyDef.position.Set(x, y);
	mainBody = world->CreateBody(bodyDef);
	mainBody->categoryBits = PLAYER_BIT;
	mainBody->maskBits = PLATFORM_BIT;
	mainBody->PutExtra(this);
}


void Player::HandleInput()
{
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

	//hold-jump 
	if (Input::GetKey(DIK_Z))
	{
		if (jumpTime < MAXJUMPTIME) //continue jumping if there is still jumptime
		{
			mainBody->SetVelocity(mainBody->GetVelocity().x, mainBody->GetVelocity().y + 0.5f);
			jumpTime += 0.02f;
		}
		else
		{
			jumpTime = 100;  //don't jump more
		}
	}
	else
	{
		jumpTime = 100; //don't jump more
	}

	//jump only if grounded
	if (Input::GetKeyDown(DIK_Z) && isGrounded)
	{
		mainBody->SetVelocity(mainBody->GetVelocity().x, 10);
		isGrounded = false;
		jumpTime = 0;
	}
}

void Player::Render(SpriteBatch *batch)
{	
	//draw player
	batch->Draw(*this);
}


void Player::Update(float dt)
{
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
			SetRegion(*movingAnimation.Next(dt));
		}
		else
		{
			SetRegion(*standingAnimation.Next(dt));
		}
	}

	//update sprite position
	SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);
}

void Player::Release()
{

}
