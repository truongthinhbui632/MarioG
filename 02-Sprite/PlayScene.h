#pragma once
#include "HanabiScene.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"
#include "HanabiShape.h"

#define PLAYERAPPEARINGTIME 0.1
enum SoundTheme { Brinstar, KraidTheme, MotherBrainTheme };

class PlayScene : public Scene
{
private:

	//Camera
	Camera cam;
	//load map
	TMXLoader mapLoader;
	TMXMap* map;

	//draw texture, sprite, ...
	SpriteBatch* batch;

public:
	PlayScene();
	~PlayScene();

	void SetBatch(SpriteBatch* batch);
	void HandlePhysics(float dt);
	void Render();

	void Create() override;
	void Update(float dt) override;
	void Release() override;
	bool isOver();
};

