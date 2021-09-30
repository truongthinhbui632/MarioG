#pragma once

#include "HanabiGame.h"
#include "PlayScene.h"

class MarioGame : public Game
{
private:
	SpriteBatch batch;
	PlayScene playScene;
	float pauseTime;
	Scene* scenes;
protected:
	//create all the things of a game here, such as world, object, ...
	void CreateGame() override;
	//update game by one frame (render, control game) - just write your game here
	void UpdateGame(float dt) override;


public:
	MarioGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~MarioGame();
	void Release() override;
};