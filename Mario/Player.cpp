#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{

}


void Player::Create(float x, float y)
{
	//get characterTexture
	texture = Texture("Resources/mariofullsheet.png");


	TexturePacker p = TexturePacker(&texture, "Resources/mario_packer.xml");

	SetRegion(p.GetRegion("standing").at(0));
	SetSize(34, 60);
	SetPosition(x, y);
}


void Player::HandleInput()
{
	//Move right
	if (Input::GetKey(DIK_RIGHT))
	{
		this->SetPosition(this->GetPosition().x + 5, this->GetPosition().y);
	}

	//move left
	if (Input::GetKey(DIK_LEFT))
	{
		this->SetPosition(this->GetPosition().x - 5, this->GetPosition().y);
	}
}

void Player::Render(SpriteBatch *batch)
{	
	//draw player
	batch->Draw(*this);
}


void Player::Update(float dt)
{

}
