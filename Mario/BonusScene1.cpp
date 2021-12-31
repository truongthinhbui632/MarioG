#include "BonusScene1.h"

#define RENDERDEBUGBOX 1

BonusScene1::BonusScene1()
{
}


BonusScene1::~BonusScene1()
{
}

void BonusScene1::SetBatch(SpriteBatch* batch)
{
	this->batch = batch;
	//set the camera to be used by this batch
	batch->SetCamera(&cam);
}

void BonusScene1::Create()
{
	//world
	world.SetGravity(-19);
	world.SetContactListener(&worldListener);

	//load map
	mapLoader.AddMap("map1", "Resources/bonus_world1_1.tmx", 1.5);
	map = mapLoader.GetMap("map1");


	//create platform
	std::vector<Shape::Rectangle> platformRects = map->GetObjectGroup("Platforms")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = platformRects.begin(); rect != platformRects.end(); ++rect)
	{
		Platform platform(&world, rect->x, rect->y, rect->width, rect->height);
	}

	//get player position
	Shape::Rectangle playerRect = map->GetObjectGroup("Player")->GetRects().front();
	player.Create(&world, playerRect.x, playerRect.y);
	startingPosition.Set(playerRect.x, playerRect.y);

	//set cam position
	cam.SetPosition(640 / 2, 480 / 2);


	objectsTexture = Texture("Resources/objects.png");
	//Coins
	std::vector<Shape::Rectangle> coinRects = map->GetObjectGroup("Coins")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = coinRects.begin(); rect != coinRects.end(); ++rect)
	{
		Coin* coin = new Coin();
		coin->Create(&world, &objectsTexture, rect->x, rect->y);
		coins.push_back(coin);
	}

	//Portals
	std::vector<Shape::Rectangle> portalRects = map->GetObjectGroup("Portals")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = portalRects.begin(); rect != portalRects.end(); ++rect)
	{
		portal.Create(&world, &objectsTexture, rect->x, rect->y);
	}
}

void BonusScene1::HandlePhysics(float dt)
{
	//handle input of player
	player.HandleInput(dt);

	if (Input::GetKeyDown(DIK_UP) && player.isOnPortal)
	{
		isSwitchToMainScene = true;
	}

	world.Update(dt);
}

void BonusScene1::MovePlayerToPortal()
{
	player.SetBodyPosition(startingPosition.x, startingPosition.y);
	player.isOnPortal = false;
}

void BonusScene1::Render()
{
	//start drawing
	batch->Begin();

	//render map
	map->Render(batch);

	//render player
	player.Render(batch);

	//render coins
	for (std::vector<Coin*>::iterator it = coins.begin(); it != coins.end(); ++it)
	{
		(*it)->Render(batch);
	}

#if RENDERDEBUGBOX
	//draw bodies
	world.RenderBodiesDebug(batch);

#endif

	//end drawing
	batch->End();
}


void BonusScene1::Update(float dt)
{

	HandlePhysics(dt);

	player.Update(dt);

	//update camera
	if (player.GetPosition().y > cam.GetPosition().y + 150)
	{
		cam.SetPosition(cam.GetPosition().x, player.GetPosition().y - 150);
	}
	else
	{
		if (player.GetPosition().y < cam.GetPosition().y - 150)
		{
			cam.SetPosition(cam.GetPosition().x, player.GetPosition().y + 150);
		}
	}

	cam.SetPosition(player.GetPosition().x > 640 / 2 ? player.GetPosition().x : 640 / 2, 480 / 2);


	//update coins
	for (int i = 0; i < coins.size(); i++)
	{
		Coin* coin = coins[i];
		coin->Update(dt);
	}

	//RENDER
	Render();
}

void BonusScene1::Release()
{
	world.Release();
	player.Release();

	for (std::vector<Coin*>::iterator it = coins.begin(); it != coins.end(); ++it)
	{
		delete* it;
		*it = NULL;
	}
}

bool BonusScene1::isOver()
{
	return false;
}