#include "Koopa.h"

Koopa::Koopa()
{
}


Koopa::~Koopa()
{
}

void Koopa::Create(World* world, Texture* goombaTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(goombaTexture, "Resources/enemies_packer.xml");

	koopaMovingAnimation.AddRegion(p.GetRegion("koopamoving"));
	koopaStaticAnimation.AddRegion(p.GetRegion("koopastatic"));
	koopaRollingAnimation.AddRegion(p.GetRegion("kooparolling"));

	SetRegion(*koopaMovingAnimation.GetKeyAnimation());
	SetSize(18 * 1.5, 18 * 1.5);
	SetPosition(x, y);

	Flip(true, false);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(16 * 1.5, 16 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = KOOPA_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | FOOT_BIT;
	body->PutExtra(this);

	health = 3;
	velocityX = -1;
	invincibleTime = 0;
}


void Koopa::Render(SpriteBatch* batch)
{
	//if (isDead) return;

	batch->Draw(*this);
}

void Koopa::Update(float dt)
{
	//if (isDead)
	//{
	//	if (body != nullptr)
	//	{
	//		world->DestroyBody(body);
	//		body = nullptr;
	//	}
	//	return;
	//}

	if (health > 2)
	{
		SetRegion(*koopaMovingAnimation.Next(dt));
	}
	else
	{
		if (health > 1)
		{
			SetRegion(*koopaStaticAnimation.Next(dt));
		}
		else
		{
			SetRegion(*koopaRollingAnimation.Next(dt));
		}
	}

	if (invincibleTime > 0)
	{
		invincibleTime -= dt;
	}

	if (shellTime > 0)
	{
		shellTime -= dt;

		if (shellTime <= 1)
		{
			flickeringTime -= dt;
			if (flickeringTime < 0)
			{
				SetRegion(TextureRegion());
				flickeringTime = 0.05f;
			}
		}

		if (shellTime <= 0)
		{
			isInShell = false;
			body->maskBits = PLAYER_BIT | PLATFORM_BIT | FOOT_BIT;
			health = 3;
			velocityX = -1;
		}
	}

	body->SetVelocity(velocityX, body->GetVelocity().y);

	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void Koopa::OnHitOnTheHead(bool right)
{
	if (invincibleTime > 0) return;
	invincibleTime = KOOPAINVINCIBLETIME;
	
	isInShell = true;
	shellTime = 5;
	flickeringTime = 0.1f;

	health--;
	if (health <= 0)
	{
		//isDead = true;
		//body->maskBits = 0;
	}
	else
	{
		if (health <= 1)
		{
			if (right)
			{
				velocityX = 5;
			}
			else
			{
				velocityX = -5;
			}

			body->maskBits = PLAYER_BIT | PLATFORM_BIT | FOOT_BIT | GOOMBA_BIT | WINGGOOMBA_BIT | QUESTIONBRICK_BIT;
		}
		else
		{
			velocityX = 0;
			body->SetSize(16 * 1.5, 12 * 1.5);
		}
	}
}

void Koopa::ChangeDirection()
{
	velocityX = -velocityX;
	Flip(velocityX > 0 ? false : true, false);
}

bool Koopa::IsInShell()
{
	return isInShell;
}