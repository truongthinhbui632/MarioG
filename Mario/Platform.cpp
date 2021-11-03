#include "Platform.h"



Platform::Platform()
{
}


Platform::~Platform()
{
}

Platform::Platform(World* world, float x, float y, float width, float height)
{
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.size.Set(width, height);
	bodyDef.position.Set(x, y);
	Body* body = world->CreateBody(bodyDef);
	body->categoryBits = PLATFORM_BIT;
	body->maskBits = PLAYER_BIT | GOOMBA_BIT | WINGGOOMBA_BIT | FOOT_BIT | MUSHROOM_BIT | KOOPA_BIT;

}