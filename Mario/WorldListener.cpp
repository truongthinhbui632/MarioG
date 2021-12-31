#include "WorldListener.h"



WorldListener::WorldListener()
{

}


WorldListener::~WorldListener()
{
}


void WorldListener::OnCollisionEnter(Body* bodyA, Body* bodyB, const Vector2& CollisionDirection)
{
	switch (bodyA->categoryBits + bodyB->categoryBits)
	{
	case PLAYER_BIT + DEADPLATFORM_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->DamagePlayer(true);
		}
		break;
	}
	case PLAYER_BIT + COINBRICK_BIT:
	{
		if (bodyB->categoryBits == COINBRICK_BIT)
		{
			CoinBrick* coinBrick = (CoinBrick*)(bodyB->GetExtra());
			coinBrick->Destroy();
		}
		else
		{
			if (bodyA->categoryBits == COINBRICK_BIT)
			{
				CoinBrick* coinBrick = (CoinBrick*)(bodyA->GetExtra());
				coinBrick->Destroy();
			}
		}
		break;
	}
	case GOOMBA_BIT + PLATFORM_BIT:
	{
		if (bodyA->categoryBits == GOOMBA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			Goomba* goomba = (Goomba*)(bodyA->GetExtra());
			goomba->ChangeDirection();
		}
		break;
	}
	case GOOMBA_BIT + QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == GOOMBA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			Goomba* goomba = (Goomba*)(bodyA->GetExtra());
			goomba->ChangeDirection();
		}
		break;
	}
	case WINGGOOMBA_BIT + PLATFORM_BIT:
	{
		if (bodyA->categoryBits == WINGGOOMBA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			WingGoomba* wingGoomba = (WingGoomba*)(bodyA->GetExtra());
			wingGoomba->ChangeDirection();
		}
		break;
	}
	case KOOPA_BIT + PLATFORM_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			Koopa* koopa = (Koopa*)(bodyA->GetExtra());
			koopa->ChangeDirection();
		}
		break;
	}
	case KOOPA_BIT + QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT && CollisionDirection.y == NOT_COLLIDED)
		{
			Koopa* koopa = (Koopa*)(bodyA->GetExtra());
			koopa->ChangeDirection();
			QuestionBrick* questionBrick = (QuestionBrick*)(bodyB->GetExtra());
			questionBrick->OnBeingHit();
		}
		break;
	}
	case KOOPA_BIT + GOOMBA_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT)
		{
			Goomba* goomba = (Goomba*)(bodyB->GetExtra());
			goomba->OnHitOnTheHead();
		}
		else
		{
			if (bodyB->categoryBits == KOOPA_BIT)
			{
				Goomba* goomba = (Goomba*)(bodyA->GetExtra());
				goomba->OnHitOnTheHead();
			}
		}
		break;
	}
	case KOOPA_BIT + WINGGOOMBA_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT)
		{
			WingGoomba* goomba = (WingGoomba*)(bodyB->GetExtra());
			goomba->OnHitOnTheHead();
		}
		else
		{
			if (bodyB->categoryBits == KOOPA_BIT)
			{
				WingGoomba* goomba = (WingGoomba*)(bodyA->GetExtra());
				goomba->OnHitOnTheHead();
			}
		}
		break;
	}
	case GOOMBA_BIT + PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				Goomba* goomba = (Goomba*)(bodyB->GetExtra());
				if (player->TailAtk())
				{
					goomba->OnHitOnTheHead();
				}
				else
					player->DamagePlayer();
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Player* player = (Player*)(bodyB->GetExtra());
				Goomba* goomba = (Goomba*)(bodyA->GetExtra());
				if (player->TailAtk())
				{
					goomba->OnHitOnTheHead();
				}
				else
					player->DamagePlayer();
			}
		}
		break;
	}
	case WINGGOOMBA_BIT + PLAYER_BIT:
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
	case KOOPA_BIT + PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Koopa* koopa = (Koopa*)(bodyB->GetExtra());
				Player* player = (Player*)(bodyA->GetExtra());

				//if koopa is in shell state, player pick up koopa
				if (koopa->IsInShell())
				{
					player->PickUpKoopa(koopa);
				}
				else
				{
					player->DamagePlayer();
				}
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (CollisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Koopa* koopa = (Koopa*)(bodyA->GetExtra());
				Player* player = (Player*)(bodyB->GetExtra());

				//if koopa is in shell state, player pick up koopa
				if (koopa->IsInShell())
				{
					player->PickUpKoopa(koopa);
				}
				else
				{
					player->DamagePlayer();
				}
			}
		}
		break;
	}
	case PLAYER_BIT + MUSHROOM_BIT:
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
	case PLAYER_BIT + LEAF_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->BecomRacoon();
			Leaf * leaf = (Leaf*)(bodyB->GetExtra());
			leaf->OnHitPlayer();
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->BecomRacoon();
			Leaf* leaf = (Leaf*)(bodyA->GetExtra());
			leaf->OnHitPlayer();
		}
		break;
	}
	}
}

void  WorldListener::OnColliding(Body* bodyA, Body* bodyB, const Vector2& collisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case PLAYER_BIT * DEADPLATFORM_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->DamagePlayer(true);
		}
		break;
	}
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
	case KOOPA_BIT* PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			if (collisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				Koopa* koopa = (Koopa*)(bodyB->GetExtra());
				Player* player = (Player*)(bodyA->GetExtra());
				//if koopa is in shell state, player pick up koopa
				if (koopa->IsInShell())
				{
					player->PickUpKoopa(koopa);
				}
				else
				{
					player->DamagePlayer();
				}
			}
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			if (collisionDirection.y == NOT_COLLIDED || bodyA->GetPosition().y > bodyB->GetPosition().y)
			{
				Koopa* koopa = (Koopa*)(bodyA->GetExtra());
				Player* player = (Player*)(bodyB->GetExtra());

				//if koopa is in shell state, player pick up koopa
				if (koopa->IsInShell())
				{
					player->PickUpKoopa(koopa);
				}
				else
				{
					player->DamagePlayer();
				}
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
	case KOOPA_BIT* GOOMBA_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT)
		{
			Goomba* goomba = (Goomba*)(bodyB->GetExtra());
			goomba->OnHitOnTheHead();
		}
		else
		{
			if (bodyB->categoryBits == KOOPA_BIT)
			{
				Goomba* goomba = (Goomba*)(bodyA->GetExtra());
				goomba->OnHitOnTheHead();
			}
		}
		break;
	}
	case KOOPA_BIT* WINGGOOMBA_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT)
		{
			WingGoomba* goomba = (WingGoomba*)(bodyB->GetExtra());
			goomba->OnHitOnTheHead();
		}
		else
		{
			if (bodyB->categoryBits == KOOPA_BIT)
			{
				WingGoomba* goomba = (WingGoomba*)(bodyA->GetExtra());
				goomba->OnHitOnTheHead();
			}
		}
		break;
	}
	case PLAYER_BIT * LEAF_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->BecomRacoon();
			Leaf* leaf = (Leaf*)(bodyB->GetExtra());
			leaf->OnHitPlayer();
		}
		else if (bodyB->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->BecomRacoon();
			Leaf* leaf = (Leaf*)(bodyA->GetExtra());
			leaf->OnHitPlayer();
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
	case PLAYER_BIT* COIN_BIT:
	{
		if (bodyB->categoryBits == COIN_BIT)
		{
			Coin* coin = (Coin*)(bodyB->GetExtra());
			coin->Destroy();
		}
		else
		{
			if (bodyA->categoryBits == COIN_BIT)
			{
				Coin* coin = (Coin*)(bodyA->GetExtra());
				coin->Destroy();
			}
		}
		break;
	}
	case PLAYER_BIT* COINBRICK_BIT:
	{
		if (bodyB->categoryBits == COINBRICK_BIT)
		{
			CoinBrick* coin = (CoinBrick*)(bodyB->GetExtra());
			coin->Destroy();
		}
		else
		{
			if (bodyA->categoryBits == COINBRICK_BIT)
			{
				CoinBrick* coin = (CoinBrick*)(bodyA->GetExtra());
				coin->Destroy();
			}
		}
		break;
	}
	case FOOT_BIT* PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT* COINBRICK_BIT:
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
	case FOOT_BIT* KOOPA_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
			Koopa* koopa = (Koopa*)(bodyA->GetExtra());
			koopa->OnHitOnTheHead(player->GetPosition().x < koopa->GetPosition().x);
		}
		else
		{
			if (bodyB->categoryBits == KOOPA_BIT)
			{
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
				Koopa* koopa = (Koopa*)(bodyB->GetExtra());
				koopa->OnHitOnTheHead(player->GetPosition().x < koopa->GetPosition().x);
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
	switch (bodyA->categoryBits + bodyB->categoryBits)
	{
	case FOOT_BIT + PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT + QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT + GOOMBA_BIT:
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
	case FOOT_BIT + WINGGOOMBA_BIT:
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
	case FOOT_BIT + KOOPA_BIT:
	{
		if (bodyA->categoryBits == KOOPA_BIT)
		{
			Koopa* koopa = (Koopa*)(bodyA->GetExtra());
			Player* player = (Player*)(bodyB->GetExtra());
			player->JumpWhenKillEnemies();
			koopa->OnHitOnTheHead(player->GetPosition().x < koopa->GetPosition().x);
		}
		else
		{
			if (bodyB->categoryBits == KOOPA_BIT)
			{
				Koopa* koopa = (Koopa*)(bodyB->GetExtra());
				Player* player = (Player*)(bodyA->GetExtra());
				player->JumpWhenKillEnemies();
				koopa->OnHitOnTheHead(player->GetPosition().x < koopa->GetPosition().x);
			}
		}
		break;
	}
	case HEAD_BIT + QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == HEAD_BIT)
		{
			QuestionBrick* questionBrick = (QuestionBrick*)(bodyB->GetExtra());
			questionBrick->OnBeingHit();
		}
		break;
	}
	case PLAYER_BIT + PORTAL_BIT:
	{
		if (bodyA->categoryBits == PORTAL_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->SetOnPortal(true);
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
	case FOOT_BIT* QUESTIONBRICK_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player* player = (Player*)(bodyA->GetExtra());
			player->OnExitGround();
		}
		break;
	}
	case PLAYER_BIT * PORTAL_BIT:
	{
		if (bodyA->categoryBits == PORTAL_BIT)
		{
			Player* player = (Player*)(bodyB->GetExtra());
			player->SetOnPortal(false);
		}
		break;
	}
	}
}