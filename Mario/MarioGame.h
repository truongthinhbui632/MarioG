#pragma once

#include "HanabiGame.h"
#include "PlayScene.h"
#include "IntroScene.h"
#include "StartScene.h"
#include "GameOverScene.h"
#include "BonusScene1.h"

class MarioGame : public Game
{
private:
	SpriteBatch batch1;
	SpriteBatch batch2;
	PlayScene playScene;
	IntroScene introScene;
	StartScene startScene;
	BonusScene1 bonusScene1;
	GameOverScene gameOverScene;
	float pauseTime;
	Scene *scenes;
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