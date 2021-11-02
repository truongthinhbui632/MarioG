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
	case GOOMBA_BIT * PLATFORM_BIT:
	{
		if (bodyA->categoryBits == GOOMBA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			Goomba* goomba = (Goomba*)(bodyA->GetExtra());
			goomba->ChangeDirection();
		}
		break;
	}
	case WINGGOOMBA_BIT * PLATFORM_BIT:
	{
		if (bodyA->categoryBits == WINGGOOMBA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			WingGoomba* wingGoomba = (WingGoomba*)(bodyA->GetExtra());
			wingGoomba->ChangeDirection();
		}
		break;
	}
	case GOOMBA_BIT* PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->DamagePlayer();
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				player->DamagePlayer();
			}
		}
		break;
	}
	case WINGGOOMBA_BIT* PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->DamagePlayer();
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				player->DamagePlayer();
			}
		}
		break;
	}
	case PLAYER_BIT* MUSHROOM_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->BecomeBig();
			MushRoom* mushRoom = (MushRoom*)(bodyB->GetExtra());
			mushRoom->OnHitPlayer();
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->BecomeBig();
			MushRoom* mushRoom = (MushRoom*)(bodyA->GetExtra());
			mushRoom->OnHitPlayer();
		}
		break;
	}
	}
}

void  WorldListener::OnColliding(Body* bodyA, Body* bodyB, const Vector2& collisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case GOOMBA_BIT* PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (collisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->DamagePlayer();
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (collisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				player->DamagePlayer();
			}
		}
		break;
	}
	case WINGGOOMBA_BIT* PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (collisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->DamagePlayer();
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (collisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				player->DamagePlayer();
			}
		}
		break;
	}
	case PLAYER_BIT * MUSHROOM_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->BecomeBig();
			MushRoom* mushRoom = (MushRoom*)(bodyB->GetExtra());
			mushRoom->OnHitPlayer();
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->BecomeBig();
			MushRoom* mushRoom = (MushRoom*)(bodyA->GetExtra());
			mushRoom->OnHitPlayer();
		}
		break;
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
	case FOOT_BIT* QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT* GOOMBA_BIT:
	{
		if (bodyA->categoryBits == GOOMBA_BIT)
		{
			Goomba* mushroom = (Goomba*)(bodyA->GetExtra());
			mushroom->OnHitOnTheHead();
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
		}
		else
		{
			if (bodyB->categoryBits == GOOMBA_BIT)
			{
				Goomba* mushroom = (Goomba*)(bodyB->GetExtra());
				mushroom->OnHitOnTheHead();
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
			}
		}
		break;
	}
	case FOOT_BIT* WINGGOOMBA_BIT:
	{
		if (bodyA->categoryBits == WINGGOOMBA_BIT)
		{
			WingGoomba* mushroom = (WingGoomba*)(bodyA->GetExtra());
			mushroom->OnHitOnTheHead();
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
		}
		else
		{
			if (bodyB->categoryBits == WINGGOOMBA_BIT)
			{
				WingGoomba* mushroom = (WingGoomba*)(bodyB->GetExtra());
				mushroom->OnHitOnTheHead();
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
			}
		}
		break;
	}
	case HEAD_BIT* QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == HEAD_BIT)
		{
			QuestionBrick* questionBrick = (QuestionBrick*)(bodyB->GetExtra());
			questionBrick->OnBeingHit();
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
	case FOOT_BIT* QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT* GOOMBA_BIT:
	{
		if (bodyA->categoryBits == GOOMBA_BIT)
		{
			Goomba* mushroom = (Goomba*)(bodyA->GetExtra());
			mushroom->OnHitOnTheHead();
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
		}
		else
		{
			if (bodyB->categoryBits == GOOMBA_BIT)
			{
				Goomba* mushroom = (Goomba*)(bodyB->GetExtra());
				mushroom->OnHitOnTheHead();
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
			}
		}
		break;
	}
	case FOOT_BIT* WINGGOOMBA_BIT:
	{
		if (bodyA->categoryBits == WINGGOOMBA_BIT)
		{
			WingGoomba* mushroom = (WingGoomba*)(bodyA->GetExtra());
			mushroom->OnHitOnTheHead();
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
		}
		else
		{
			if (bodyB->categoryBits == WINGGOOMBA_BIT)
			{
				WingGoomba* mushroom = (WingGoomba*)(bodyB->GetExtra());
				mushroom->OnHitOnTheHead();
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
			}
		}
		break;
	}
	case HEAD_BIT* QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == HEAD_BIT)
		{
			QuestionBrick* questionBrick = (QuestionBrick*)(bodyB->GetExtra());
			questionBrick->OnBeingHit();
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