#include "WingGoomba.h"

WingGoomba::WingGoomba()
{
}


WingGoomba::~WingGoomba()
{
}

void WingGoomba::Create(World* world, Texture* goombaTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(goombaTexture, "Resources/enemies_packer.xml");

	wingGoombaAnimation1.AddRegion(p.GetRegion("winggoombajumping"));
	wingGoombaAnimation2.AddRegion(p.GetRegion("winggoombawalking"));
	//mushroomAnimation.SetFrameInterval(0.04);

	SetRegion(*wingGoombaAnimation1.GetKeyAnimation());
	SetSize(18 * 1.5, 18 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(15.5f * 1.5, 15.5f * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = WINGGOOMBA_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | FOOT_BIT;
	body->PutExtra(this);

	health = 2;
	velocityX = -1;
	invincibleTime = 0;
	timeBetweenJump = 0;
}


void WingGoomba::Render(SpriteBatch* batch)
{
	if (isDead) return;

	batch->Draw(*this);
}

void WingGoomba::Update(float dt)
{
	if (isDead)
	{
		if (body != nullptr)
		{
			world->DestroyBody(body);
			body = nullptr;
		}
		return;
	}

	if (health > 1)
	{
		SetRegion(*wingGoombaAnimation1.Next(dt));
	}
	else
	{
		SetRegion(*wingGoombaAnimation2.Next(dt));
		SetSize(16 * 1.5, 16 * 1.5);
	}

	if (invincibleTime > 0)
	{
		invincibleTime -= dt;
	}

	//only jump when not hit on the head for the first time
	if (timeBetweenJump >= 0)
	{
		timeBetweenJump += dt;
	}

	if (timeBetweenJump >= WINGMUSHROOMTIMEBETWEENJUMP)
	{
		if (timeBetweenJump >= WINGMUSHROOMTIMEBETWEENJUMP + 0.3)
		{
			//actually jump
			body->SetVelocity(body->GetVelocity().x, 5);
			timeBetweenJump = 0;
		}
		else
		{
			//prepare to jump
			if (body->GetVelocity().y <= 0)
			{
				body->SetVelocity(body->GetVelocity().x, 2);
			}
		}
	}

	body->SetVelocity(velocityX, body->GetVelocity().y);

	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void WingGoomba::OnHitOnTheHead()
{
	if (invincibleTime > 0) return;
	invincibleTime = WINGMUSHROOMINVINCIBLETIME;

	health--;
	if (health == 0)
	{
		isDead = true;
		body->maskBits = 0;
	}
	else
	{
		//don't jump anymore
		timeBetweenJump = -1;
	}
}

void WingGoomba::ChangeDirection()
{
	//Flip(!IsFlipX(), IsFlipY());
	velocityX = -velocityX;
}

bool WingGoomba::IsDead()
{
	return isDead;
}