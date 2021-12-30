#pragma once
#include "HanabiScene.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"
#include "HanabiShape.h"
#include "HanabiWorld.h"
#include "WorldListener.h"
#include "Player.h"
#include "Platform.h"
#include "Coin.h"
#include "Portal.h"

class BonusScene1 : public Scene
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

	Texture objectsTexture;

	//objects
	std::vector<Coin*> coins;

	Portal portal;

	Vector2 startingPosition;

public:
	BonusScene1();
	~BonusScene1();

	bool isSwitchToMainScene = false;

	void SetBatch(SpriteBatch* batch);
	void HandlePhysics(float dt);
	void Render();

	void MovePlayerToPortal();

	void Create() override;
	void Update(float dt) override;
	void Release() override;
	bool isOver();
};

