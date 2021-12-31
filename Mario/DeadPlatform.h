#pragma once
#include "HanabiWorld.h"

#include "CollisionBit.h"

class DeadPlatform
{
public:
	DeadPlatform();
	~DeadPlatform();
	DeadPlatform(World* world, float x, float y, float width, float height);
};