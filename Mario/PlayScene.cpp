#include "PlayScene.h"

#define RENDERDEBUGBOX 1

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

void PlayScene::SetBatch(SpriteBatch* batch)
{
	this->batch = batch;
	//set the camera to be used by this batch
	batch->SetCamera(&cam);
}

void PlayScene::Create()
{
	//world
	world.SetGravity(-19);
	world.SetContactListener(&worldListener);

	//load map
	mapLoader.AddMap("map1", "Resources/world1_1.tmx", 1.5f);
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

	//set cam position
	cam.SetPosition(640/2, 480/2);

	//--------------------------ENEMIES-------------------------------
	enemiesTexture = Texture("Resources/enemies2.png");

	//Mushrooms
	std::vector<Shape::Rectangle> mushRoomRects = map->GetObjectGroup("Mushrooms")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = mushRoomRects.begin(); rect != mushRoomRects.end(); ++rect)
	{
		MushRoom *mushroom = new MushRoom();
		mushroom->Create(&world, &enemiesTexture, rect->x, rect->y);
		mushrooms.push_back(mushroom);
	}
}

void PlayScene::HandlePhysics(float dt)
{
	//handle input of player
	player.HandleInput();

	world.Update(dt);
}

void  PlayScene::Render()
{
	//start drawing
	batch->Begin();

	//render map
	map->Render(batch);

	//render player
	player.Render(batch);

	//render mushrooms
	for (std::vector<MushRoom*>::iterator it = mushrooms.begin(); it != mushrooms.end(); ++it)
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


void PlayScene::Update(float dt)
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

	cam.SetPosition(player.GetPosition().x > 640/2 ? player.GetPosition().x : 640/2, 480/2);


	//update mushrooms
	for (int i = 0; i < mushrooms.size(); i++)
	{
		MushRoom* mushroom = mushrooms[i];
		mushroom->Update(dt);
		//if (mushroom->IsDead())
		//{
		//	//delete skree
		//	delete mushroom;
		//	mushroom = NULL;
		//	mushrooms.erase(mushrooms.begin() + i);
		//}
	}

	//RENDER
	Render();

}

void PlayScene::Release()
{
	world.Release();
	player.Release();


	for (std::vector<MushRoom*>::iterator it = mushrooms.begin(); it != mushrooms.end(); ++it)
	{
		delete* it;
		*it = NULL;
	}
}

bool PlayScene::isOver()
{
	return false;
}