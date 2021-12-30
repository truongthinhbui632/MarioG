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

	playScene.Create();
	playScene.SetBatch(&batch);

	SetScene(&playScene);
	scenes = &playScene;
	pauseTime = 0;
}
void MarioGame::UpdateGame(float dt)
{
	Game::UpdateGame(dt);
}

void MarioGame::Release()
{
	Game::Release();
	batch.Release();
	playScene.Release();
}

