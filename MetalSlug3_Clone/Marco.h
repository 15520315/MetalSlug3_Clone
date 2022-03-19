#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define MARCO_WIDTH 30


class CMarco : public CGameObject
{
protected:
	float vx;
public:
	CMarco(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};

class CMarcoLeg : public CGameObject
{
protected:
	float vx;
public:
	CMarcoLeg(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};
