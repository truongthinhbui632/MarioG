#pragma once
#include "HanabiScene.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"
#include "HanabiShape.h"
#include "HanabiWorld.h"
#include "WorldListener.h"
#include "Player.h"
#include "Platform.h"

class PlayScene: public Scene
{
private:

	//Camera
	Camera cam;
	//load map
	TMXLoader mapLoader;
	TMXMap* map;
	
	//World
	World world;

	//listen to collision between bodies
	WorldListener worldListener;

	//player
	Player player;

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

