#include "Goomba.h"

Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

void Goomba::Create(World* world, Texture* goombaTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(goombaTexture, "Resources/enemies_packer.xml");

	goombaAnimation.AddRegion(p.GetRegion("goomba"));
	//mushroomAnimation.SetFrameInterval(0.04);

	SetRegion(*goombaAnimation.GetKeyAnimation());
	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(15.5 * 1.5, 15.5 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = GOOMBA_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | FOOT_BIT | KOOPA_BIT | QUESTIONBRICK_BIT;
	body->PutExtra(this);

	velocityX = -1;
}


void Goomba::Render(SpriteBatch* batch)
{
	if (isDead) return;

	batch->Draw(*this);
}

void Goomba::Update(float dt)
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

	SetRegion(*goombaAnimation.Next(dt));

	body->SetVelocity(velocityX, body->GetVelocity().y);

	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void Goomba::OnHitOnTheHead()
{
	isDead = true;
	body->maskBits = 0;
}

void Goomba::ChangeDirection()
{
	velocityX = -velocityX;
}

bool Goomba::IsDead()
{
	return isDead;
}