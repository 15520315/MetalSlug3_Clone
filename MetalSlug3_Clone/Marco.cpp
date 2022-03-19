#include "Game.h"
#include "Marco.h"

CMarco::CMarco(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
};

CMarcoLeg::CMarcoLeg(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
};

void CMarco::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARCO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARCO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARCO_WIDTH);
		}
	}
}

void CMarcoLeg::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARCO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARCO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARCO_WIDTH);
		}
	}
}

void CMarco::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx > 0) ani = CAnimations::GetInstance()->Get(500);
	else ani = CAnimations::GetInstance()->Get(500);

	ani->Render(x, y);
}

void CMarcoLeg::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx > 0) ani = CAnimations::GetInstance()->Get(510);
	else ani = CAnimations::GetInstance()->Get(510);

	ani->Render(x, y);
}