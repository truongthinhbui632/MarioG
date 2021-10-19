#include "MushRoom.h"

MushRoom::MushRoom()
{
}


MushRoom::~MushRoom()
{
}

void MushRoom::Create(World* world, Texture* mushRoomTexture, int x, int y)
{
	this->world = world;
	TexturePacker p = TexturePacker(mushRoomTexture, "Resources/enemies_packer.xml");

	mushroomAnimation.AddRegion(p.GetRegion("mushroom"));
	//mushroomAnimation.SetFrameInterval(0.04);

	SetRegion(*mushroomAnimation.GetKeyAnimation());
	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(16 * 1.5, 16 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = MUSHROOM_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | FOOT_BIT;
	body->PutExtra(this);

	body->SetVelocity(-1, 0);
}


void MushRoom::Render(SpriteBatch* batch)
{
	if (isDead) return;

	batch->Draw(*this);
}

void MushRoom::Update(float dt)
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

	SetRegion(*mushroomAnimation.Next(dt));

	//Flip(!IsFlipX(), IsFlipY());

	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void MushRoom::OnHitOnTheHead()
{
	isDead = true;
	body->maskBits = 0;
}

void MushRoom::ChangeDirection()
{
	//Flip(!IsFlipX(), IsFlipY());
	body->SetVelocity(-body->GetVelocity().x, 0);
}

bool MushRoom::IsDead()
{
	return isDead;
}