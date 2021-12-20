#include "CoinBrick.h"

CoinBrick::CoinBrick()
{
}


CoinBrick::~CoinBrick()
{
}

void CoinBrick::Create(World* world, Texture* objectsTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(objectsTexture, "Resources/objects_packer.xml");

	coinBrickAnimation.AddRegion(p.GetRegion("coinbrick"));
	normalCoinAnimation.AddRegion(p.GetRegion("coin"));

	SetRegion(*coinBrickAnimation.GetKeyAnimation());

	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(16 * 1.5, 16 * 1.5);
	bodyBrick = world->CreateBody(bodyDef);
	bodyBrick->categoryBits = COINBRICK_BIT;
	bodyBrick->maskBits = PLAYER_BIT | FOOT_BIT;
	bodyBrick->PutExtra(this);

	BodyDef bodyDef2;
	bodyDef2.bodyType = Body::BodyType::Kinematic;
	bodyDef2.isSensor = true;
	bodyDef2.position.Set(x, y);
	bodyDef2.size.Set(16 * 1.5, 16 * 1.5);
	bodyCoin = world->CreateBody(bodyDef2);
	bodyCoin->categoryBits = COINBRICK_BIT;
	bodyCoin->maskBits = PLAYER_BIT;
	bodyCoin->PutExtra(this);

	isCoin = false;
}


void CoinBrick::Render(SpriteBatch* batch)
{
	if (bodyCoin->categoryBits == 0) return;

	batch->Draw(*this);
}

void CoinBrick::Update(float dt)
{
	if (isCoin)
	{
		SetRegion(*normalCoinAnimation.Next(dt));
	}
	else
	{
		SetRegion(*coinBrickAnimation.Next(dt));
	}
}

bool CoinBrick::IsCoin()
{
	return isCoin;
}

void CoinBrick::TurnToCoin()
{
	isCoin = true;
	bodyBrick->categoryBits = 0;
}

void CoinBrick::TurnBackToBrick()
{
	if (bodyCoin->categoryBits == 0) return;
	isCoin = false;
	bodyBrick->categoryBits = COINBRICK_BIT;
}

void CoinBrick::Destroy()
{
	if (isCoin)
	{
		bodyBrick->categoryBits = 0;
		bodyCoin->categoryBits = 0;
	}
	//Add points for players
}