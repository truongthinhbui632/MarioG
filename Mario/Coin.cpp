#include "Coin.h"

Coin::Coin()
{
}


Coin::~Coin()
{
}

void Coin::Create(World* world, Texture* objectsTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(objectsTexture, "Resources/objects_packer.xml");

	coinAnimation.AddRegion(p.GetRegion("coin"));
	coinAnimation.SetFrameInterval(0.1);

	SetRegion(*coinAnimation.GetKeyAnimation());
	SetSize(10 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.isSensor = true;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(10 * 1.5, 16 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = COIN_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);
}


void Coin::Render(SpriteBatch* batch)
{
	if (body->categoryBits == 0) return;

	batch->Draw(*this);
}

void Coin::Update(float dt)
{
	SetRegion(*coinAnimation.Next(dt));
}

void Coin::Destroy()
{
	body->categoryBits = 0;

	//Add points for players
}