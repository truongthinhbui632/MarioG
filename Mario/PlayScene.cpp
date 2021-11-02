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
	std::vector<Shape::Rectangle> goombaRects = map->GetObjectGroup("Mushrooms")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = goombaRects.begin(); rect != goombaRects.end(); ++rect)
	{
		Goomba *goomba = new Goomba();
		goomba->Create(&world, &enemiesTexture, rect->x, rect->y);
		goombas.push_back(goomba);
	}

	//WingMushrooms
	std::vector<Shape::Rectangle> wingGoombaRects = map->GetObjectGroup("WingMushrooms")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = wingGoombaRects.begin(); rect != wingGoombaRects.end(); ++rect)
	{
		WingGoomba* winggoomba = new WingGoomba();
		winggoomba->Create(&world, &enemiesTexture, rect->x, rect->y);
		wingGoombas.push_back(winggoomba);
	}

	objectsTexture = Texture("Resources/objects.png");

	//CoinQuestionBricks
	std::vector<Shape::Rectangle> coinQuestionBrickRects = map->GetObjectGroup("CoinQuestionBricks")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = coinQuestionBrickRects.begin(); rect != coinQuestionBrickRects.end(); ++rect)
	{
		QuestionBrick* questionBrick = new QuestionBrick();
		questionBrick->Create(&world, &objectsTexture, QuestionBrick::BrickType::CoinType, rect->x, rect->y);
		questionBricks.push_back(questionBrick);
	}

	//MushRoomQuestionBricks
	std::vector<Shape::Rectangle> mushRoomQuestionBrickRects = map->GetObjectGroup("MushRoomQuestionBricks")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = mushRoomQuestionBrickRects.begin(); rect != mushRoomQuestionBrickRects.end(); ++rect)
	{
		QuestionBrick* questionBrick = new QuestionBrick();
		questionBrick->Create(&world, &objectsTexture, QuestionBrick::BrickType::MushRoomType, rect->x, rect->y);
		questionBricks.push_back(questionBrick);
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
	for (std::vector<Goomba*>::iterator it = goombas.begin(); it != goombas.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render wingMushrooms
	for (std::vector<WingGoomba*>::iterator it = wingGoombas.begin(); it != wingGoombas.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render questionBricks
	for (std::vector<QuestionBrick*>::iterator it = questionBricks.begin(); it != questionBricks.end(); ++it)
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
	for (int i = 0; i < goombas.size(); i++)
	{
		Goomba* goomba = goombas[i];
		goomba->Update(dt);
		//if (mushroom->IsDead())
		//{
		//	//delete skree
		//	delete mushroom;
		//	mushroom = NULL;
		//	mushrooms.erase(mushrooms.begin() + i);
		//}
	}

	//update wingmushrooms
	for (int i = 0; i < wingGoombas.size(); i++)
	{
		WingGoomba* wingGoomba = wingGoombas[i];
		wingGoomba->Update(dt);
	}

	//update questionBricks
	for (int i = 0; i < questionBricks.size(); i++)
	{
		QuestionBrick* questionBrick = questionBricks[i];
		questionBrick->Update(dt);
	}

	//RENDER
	Render();

}

void PlayScene::Release()
{
	world.Release();
	player.Release();


	for (std::vector<Goomba*>::iterator it = goombas.begin(); it != goombas.end(); ++it)
	{
		delete* it;
		*it = NULL;
	}

	for (std::vector<WingGoomba*>::iterator it = wingGoombas.begin(); it != wingGoombas.end(); ++it)
	{
		delete* it;
		*it = NULL;
	}

	for (std::vector<QuestionBrick*>::iterator it = questionBricks.begin(); it != questionBricks.end(); ++it)
	{
		delete* it;
		*it = NULL;
	}
}

bool PlayScene::isOver()
{
	return false;
}