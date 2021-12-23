#include "QuestionBrick.h"

QuestionBrick::QuestionBrick()
{
}


QuestionBrick::~QuestionBrick()
{
}

void QuestionBrick::Create(World* world, Texture* objectsTexture, BrickType brickType, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(objectsTexture, "Resources/objects_packer.xml");

	brickAnimation.AddRegion(p.GetRegion("questionbrick"));
	brickAnimation.SetFrameInterval(0.1f);
	brickAnimationStatic.AddRegion(p.GetRegion("questionbrickstatic"));

	SetRegion(*brickAnimation.GetKeyAnimation());
	SetSize(16 * 1.5, 16 * 1.5);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(16 * 1.5, 16 * 1.5);
	body = world->CreateBody(bodyDef);
	body->categoryBits = QUESTIONBRICK_BIT;
	body->maskBits = PLAYER_BIT | FOOT_BIT | HEAD_BIT | MUSHROOM_BIT | GOOMBA_BIT | KOOPA_BIT | LEAF_BIT;
	body->PutExtra(this);

	this->objectsTexture = objectsTexture;
	this->brickType = brickType;

	isAlreadyHit = false;
}


void QuestionBrick::Render(SpriteBatch* batch)
{
	batch->Draw(*this);


	if (isAlreadyHit)
	{
		switch (brickType)
		{
		case QuestionBrick::CoinType:
			break;
		case QuestionBrick::MushRoomType:
		{
			mushRoom.Render(batch);
			break;
		}
		case QuestionBrick::WingType:
			leaf.Render(batch);
			break;
		}
	}
}

void QuestionBrick::Update(float dt)
{
	if (isAlreadyHit)
	{
		SetRegion(*brickAnimationStatic.Next(dt));

		switch (brickType)
		{
		case QuestionBrick::CoinType:
			break;
		case QuestionBrick::MushRoomType:
		{
			mushRoom.Update(dt);
			break;
		}
		case QuestionBrick::WingType:
			leaf.Update(dt);
			break;
		}
	}
	else
	{
		SetRegion(*brickAnimation.Next(dt));
	}
}


void QuestionBrick::OnBeingHit()
{
	if (isAlreadyHit) return;

	switch (brickType)
	{
	case QuestionBrick::CoinType:
		break;
	case QuestionBrick::MushRoomType:
	{
		mushRoom.Create(world, objectsTexture, body->GetPosition().x, body->GetPosition().y + 16 * 1.5f);
		break;
	}
	case QuestionBrick::WingType:
		leaf.Create(world, objectsTexture, body->GetPosition().x, body->GetPosition().y + 16 * 1.5f);
		break;
	}

	isAlreadyHit = true;
}