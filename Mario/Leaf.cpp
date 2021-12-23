#include "Leaf.h"

Leaf::Leaf()
{
}


Leaf::~Leaf()
{
}

void Leaf::Create(World* world, Texture* leafTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(leafTexture, "Resources/objects_packer.xml");

	leafAnimation.AddRegion(p.GetRegion("leaf"));
	//mushroomAnimation.SetFrameInterval(0.04);

	SetRegion(*leafAnimation.GetKeyAnimation());
	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(15.5 * 1.5, 15.5 * 1.5);
	bodyDef.mass = 0.5f;
	body = world->CreateBody(bodyDef);
	body->categoryBits = LEAF_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | QUESTIONBRICK_BIT;
	body->PutExtra(this);

	isEaten = false;
	
	timeToChangeDirection = 0;
	timeToStop = 1;
	speed = 2;

	body->SetVelocity(speed, 5);
}


void Leaf::Render(SpriteBatch* batch)
{
	if (isEaten) return;

	batch->Draw(*this);
}

void Leaf::Update(float dt)
{
	if (isEaten)
	{
		if (body != nullptr)
		{
			world->DestroyBody(body);
			body = nullptr;
		}
		return;
	}

	SetRegion(*leafAnimation.Next(dt));

	if (timeToStop > 0)
	{
		if (timeToChangeDirection > 0.1f)
		{
			speed = -speed;
			body->SetVelocity(speed, body->GetVelocity().y);
			timeToChangeDirection = 0;
		}
		else
		{
			timeToChangeDirection += dt;
		}
		timeToStop -= dt;
	}

	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void Leaf::OnHitPlayer()
{
	isEaten = true;
	body->maskBits = 0;
}