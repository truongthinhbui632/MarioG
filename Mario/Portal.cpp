#include "Portal.h"

Portal::Portal()
{
}


Portal::~Portal()
{
}

void Portal::Create(World* world, Texture* leafTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(leafTexture, "Resources/objects_packer.xml");

	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.isSensor = true;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(25 * 1.5, 25 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = PORTAL_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);
}


void Portal::Render(SpriteBatch* batch)
{
	batch->Draw(*this);
}

void Portal::Update(float dt)
{
	
}