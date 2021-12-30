#include "MarioGame.h"

#define USEMAP1 1

MarioGame::MarioGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MarioGame::~MarioGame()
{
	
}


void MarioGame::CreateGame()
{

	//create batch to draw everything
	batch1.Create();
	batch2.Create();

	//// 1/intro scene
	//introScene.Create();
	//introScene.SetBatch(&batch);

	//// 2/start scene
	//startScene.Create();
	//startScene.SetBatch(&batch);

	// 3/play screen
	playScene = new PlayScene();
	playScene->Create();
	playScene->SetBatch(&batch1);

	bonusScene1 = new BonusScene1();
	bonusScene1->Create();
	bonusScene1->SetBatch(&batch2);

	//// 4/gameover scene
	//gameOverScene.Create();
	//gameOverScene.SetBatch(&batch);


	SetScene(playScene);
	scenes = playScene;
	pauseTime = 0;
}
void MarioGame::UpdateGame(float dt)
{
	Game::UpdateGame(dt);
	
	if (scenes == playScene)
	{
		if (playScene->isSwitchToBonusScene == true)
		{
			SetScene(bonusScene1);
			bonusScene1->MovePlayerToPortal();
			scenes = bonusScene1;
			playScene->isSwitchToBonusScene = false;
		}
	}

	if (scenes == bonusScene1)
	{
		if (bonusScene1->isSwitchToMainScene == true)
		{
			SetScene(playScene);
			playScene->MovePlayerToPortal();
			scenes = playScene;
			bonusScene1->isSwitchToMainScene = false;
		}
	}

	if (playScene->IsPlayerDead())
	{
		PlayScene* newPlayScene = new PlayScene();
		newPlayScene->Create();
		newPlayScene->SetBatch(&batch1);
		playScene->Release();
		delete playScene;
		playScene = newPlayScene;
		SetScene(playScene);
	}

	/*if (Input::GetKeyDown(DIK_ESCAPE))
	{
		ShutDownApplication();
	}
	if (Input::GetKeyDown(DIK_RETURN))
	{
		if (scenes == &introScene)
		{
			SetScene(&startScene);
			startScene.SetBatch(&batch);
			scenes = &startScene;
		}
		else if (scenes == &startScene)
		{
			SetScene(&playScene);
			playScene.SetBatch(&batch);
			scenes = &playScene;
		}
	}
	if (playScene.isOver() == true)
	{
		pauseTime += 1;

		if (pauseTime > 40)
		{
			SetScene(&gameOverScene);
			gameOverScene.SetBatch(&batch);
			scenes = &gameOverScene;
		}
	}*/


}

void MarioGame::Release()
{
	Game::Release();
	batch1.Release();
	batch2.Release();
	playScene->Release();
	bonusScene1->Release();
	delete playScene;
	delete bonusScene1;
}

