#include "WorldListener.h"



WorldListener::WorldListener()
{

}


WorldListener::~WorldListener()
{
}


void WorldListener::OnCollisionEnter(Body* bodyA, Body* bodyB, const Vector2& CollisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case MUSHROOM_BIT * PLATFORM_BIT:
	{
		if (bodyA->categoryBits == MUSHROOM_BIT)
		{
			MushRoom* mushroom = (MushRoom*)(bodyA->GetExtra());
			mushroom->ChangeDirection();
		}
		break;
	}
	case MUSHROOM_BIT* PLAYER_BIT:
	{
		if (CollisionDirection.y == NOT_COLLIDED)
		{
			if (bodyA->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->DamagePlayer();
			}
			else if (bodyB->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				player->DamagePlayer();
			}
			break;
		}
	}
	}
}

void  WorldListener::OnColliding(Body* bodyA, Body* bodyB, const Vector2& collisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case MUSHROOM_BIT* PLAYER_BIT:
	{
		if (collisionDirection.y == NOT_COLLIDED)
		{
			if (bodyA->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->DamagePlayer();
			}
			else if (bodyB->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				player->DamagePlayer();
			}
			break;
		}
	}
	}
}


void WorldListener::OnCollisionExit(Body* bodyA, Body* bodyB, const Vector2& collisionDirection)
{

}


void WorldListener::OnSersorEnter(Body* bodyA, Body* bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case FOOT_BIT* PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT* MUSHROOM_BIT:
	{
		if (bodyA->categoryBits == MUSHROOM_BIT)
		{
			MushRoom* mushroom = (MushRoom*)(bodyA->GetExtra());
			mushroom->OnHitOnTheHead();
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
		}
		else
		{
			if (bodyB->categoryBits == MUSHROOM_BIT)
			{
				MushRoom* mushroom = (MushRoom*)(bodyB->GetExtra());
				mushroom->OnHitOnTheHead();
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
			}
		}
		break;
	}
	}
}

void WorldListener::OnSersorOverlaying(Body* bodyA, Body* bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case FOOT_BIT* PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT* MUSHROOM_BIT:
	{
		if (bodyA->categoryBits == MUSHROOM_BIT)
		{
			MushRoom* mushroom = (MushRoom*)(bodyA->GetExtra());
			mushroom->OnHitOnTheHead();
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
		}
		else
		{
			if (bodyB->categoryBits == MUSHROOM_BIT)
			{
				MushRoom* mushroom = (MushRoom*)(bodyB->GetExtra());
				mushroom->OnHitOnTheHead();
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
			}
		}
		break;
	}
	}
}

void  WorldListener::OnSensorExit(Body* bodyA, Body* bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case FOOT_BIT* PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnExitGround();
		}
		break;
	}
	}
}