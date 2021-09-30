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
	mapLoader.AddMap("map1", "map/world1-1.tmx", 1);
	map = mapLoader.GetMap("map1");

	//set cam position
	cam.SetPosition(640 / 2, 480 / 2);
}

void PlayScene::HandlePhysics(float dt)
{

}

void  PlayScene::Render()
{
	//start drawing
	batch->Begin();

	//render map
	map->Render(batch);

	//end drawing
	batch->End();
}


void PlayScene::Update(float dt)
{

	HandlePhysics(dt);

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