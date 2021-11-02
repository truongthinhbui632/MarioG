#include "MushRoom.h"

MushRoom::MushRoom()
{
}


MushRoom::~MushRoom()
{
}

void MushRoom::Create(World* world, Texture* mushroomTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(mushroomTexture, "Resources/objects_packer.xml");

	mushroomAnimation.AddRegion(p.GetRegion("mushroom"));
	//mushroomAnimation.SetFrameInterval(0.04);

	SetRegion(*mushroomAnimation.GetKeyAnimation());
	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(15.5 * 1.5, 15.5 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = MUSHROOM_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | QUESTIONBRICK_BIT;
	body->PutExtra(this);

	isEaten = false;
}


void MushRoom::Render(SpriteBatch* batch)
{
	if (isEaten) return;

	batch->Draw(*this);
}

void MushRoom::Update(float dt)
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

	SetRegion(*mushroomAnimation.Next(dt));

	body->SetVelocity(1, body->GetVelocity().y);

	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void MushRoom::OnHitPlayer()
{
	isEaten = true;
	body->maskBits = 0;
}