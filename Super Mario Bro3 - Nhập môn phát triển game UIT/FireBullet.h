#pragma once
#include "GameObject.h"
#include "Configs.h"

#define ID_ANI_FIRE 7000

#define FIRE_BOUNDED_TOP -15
#define FIRE_BOUNDED_BOTTOM 15
#define FIRE_BOUNDED_LEFT 0
#define FIRE_BOUNDED_RIGHT 175

#define FIRE_BBOX_WIDTH 8
#define FIRE_BBOX_HEIGHT 8

class CFireBullet : public CGameObject
{
	float vx, vy;

	void OnCollsionWithMario(LPCOLLISIONEVENT e);
public:
	CFireBullet(float x, float y, float vx, float vy): CGameObject(x, y)
	{
		this->vx = vx;
		this->vy = vy;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }

	int InBound() {
		return (x >= (float)FIRE_BOUNDED_LEFT * GRID_SIZE + WD_WIDTH_BUFFER && x <= (float)FIRE_BOUNDED_RIGHT * GRID_SIZE + WD_WIDTH_BUFFER)
		&& (y >= (float)FIRE_BOUNDED_TOP * GRID_SIZE + WD_HEIGHT_BUFFER && y <= (float)FIRE_BOUNDED_BOTTOM * GRID_SIZE + WD_HEIGHT_BUFFER);
	}
};