#include "HUD.h"

void HUD::Create(Texture* objectTexture, float x, float y)
{
	TexturePacker p = TexturePacker(objectTexture, "Resources/objects_packer.xml");
	
	for (int i = 0; i < 5; i++)
	{
		Sprite powerHolder;
		powerHolder.SetRegion(p.GetRegion("powerholder").at(0));
		powerHolder.SetSize(16, 16);
		powerHolders.push_back(powerHolder);

		Sprite powerHolderFiller;
		powerHolderFiller.SetRegion(p.GetRegion("powerholderfiller").at(0));
		powerHolderFiller.SetSize(16, 16);
		powerHolderFillers.push_back(powerHolderFiller);
	}

	UpdatePosition(x, y);
}

void HUD::UpdatePosition(float x, float y)
{
	for (int i = 0; i < powerHolders.size(); i++)
	{
		powerHolders[i].SetPosition(x - (2 - i) * 15, y);
	}

	for (int i = 0; i < powerHolderFillers.size(); i++)
	{
		powerHolderFillers[i].SetPosition(x - (2 - i) * 15, y);
	}
}

void HUD::UpdatePowerFiller(int power)
{
	this->power = power;
}

void HUD::Render(SpriteBatch* batch)
{
	for (int i = 0; i < powerHolders.size(); i++)
	{
		batch->Draw(powerHolders[i]);
	}

	for (int i = 0; i < powerHolderFillers.size() && i < power; i++)
	{
		batch->Draw(powerHolderFillers[i]);
	}
}