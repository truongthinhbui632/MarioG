#include "DeadPlatform.h"



DeadPlatform::DeadPlatform()
{
}


DeadPlatform::~DeadPlatform()
{
}

DeadPlatform::DeadPlatform(World* world, float x, float y, float width, float height)
{
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.size.Set(width, height);
	bodyDef.position.Set(x, y);
	Body* body = world->CreateBody(bodyDef);
	body->categoryBits = DEADPLATFORM_BIT;
	body->maskBits = PLAYER_BIT;

}