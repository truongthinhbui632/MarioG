#include "PlayScene.h"

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
	//load map
	mapLoader.AddMap("map1", "Resources/world1-1.tmx", 1);
	map = mapLoader.GetMap("map1");


	//get player position
	Shape::Rectangle playerRect = map->GetObjectGroup("Player")->GetRects().front();
	player.Create(playerRect.x, playerRect.y);

	//set cam position
	cam.SetPosition(640/2, 480/2);
}

void PlayScene::HandlePhysics(float dt)
{
	//handle input of player
	player.HandleInput();
}

void  PlayScene::Render()
{
	//start drawing
	batch->Begin();

	//render map
	map->Render(batch);
	
	//render player
	player.Render(batch);

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

	//RENDER
	Render();

}

void PlayScene::Release()
{
	
}

bool PlayScene::isOver()
{
	return false;
}