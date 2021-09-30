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
	batch.Create();

	//// 1/intro scene
	//introScene.Create();
	//introScene.SetBatch(&batch);

	//// 2/start scene
	//startScene.Create();
	//startScene.SetBatch(&batch);

	// 3/play screen
	playScene.Create();
	playScene.SetBatch(&batch);

	//// 4/gameover scene
	//gameOverScene.Create();
	//gameOverScene.SetBatch(&batch);


	SetScene(&playScene);
	scenes = &playScene;
	pauseTime = 0;
}
void MarioGame::UpdateGame(float dt)
{
	Game::UpdateGame(dt);
	
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
	batch.Release();
	playScene.Release();
}

