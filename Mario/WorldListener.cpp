#include "WorldListener.h"



WorldListener::WorldListener()
{

}


WorldListener::~WorldListener()
{
}


void WorldListener::OnCollisionEnter(Body* bodyA, Body* bodyB, const Vector2& CollisionDirection)
{
	
}

void  WorldListener::OnColliding(Body* bodyA, Body* bodyB, const Vector2& collisionDirection)
{
	
}


void WorldListener::OnCollisionExit(Body* bodyA, Body* bodyB, const Vector2& collisionDirection)
{
}


void WorldListener::OnSersorEnter(Body* bodyA, Body* bodyB)
{

}

void WorldListener::OnSersorOverlaying(Body* bodyA, Body* bodyB)
{

}

void  WorldListener::OnSensorExit(Body* bodyA, Body* bodyB)
{

}