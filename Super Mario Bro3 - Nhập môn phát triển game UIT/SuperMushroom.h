#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f


#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14
#define MUSHROOM_BBOX_HEIGHT_DIE 7

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200

#define ID_ANI_MUSHROOM_WALKING 6000
#define ID_ANI_MUSHROOM_DIE 6001

class CSuperMushroom : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CSuperMushroom(float x, float y);
	virtual void SetState(int state);
};