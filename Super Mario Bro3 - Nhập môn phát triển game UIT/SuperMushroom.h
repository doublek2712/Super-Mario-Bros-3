#pragma once
#include "GlobalState.h"
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_COMEOUT_SPEED 0.01f


#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_STATE_COMEOUT 100
#define MUSHROOM_STATE_WALKING 200
#define MUSHROOM_STATE_DIE 300


class CSuperMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float def_y;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	CSuperMushroom(float x, float y);
	virtual void SetState(int state);
};