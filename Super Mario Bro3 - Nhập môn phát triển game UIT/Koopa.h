#pragma once
#include "GameObject.h"

#define KOOBA_GRAVITY 0.002f
#define KOOBA_WALKING_SPEED 0.05f


#define KOOBA_BBOX_WIDTH 16
#define KOOBA_BBOX_HEIGHT 26

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	int isBlockByPlatform;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int block);
	virtual void SetState(int state);
};
