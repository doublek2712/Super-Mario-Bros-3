#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.0004f
#define GOOMBA_WALKING_SPEED 0.03f
#define GOOMBA_HIT_DEFLECT_SPEED 0.2f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 12
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_HIT_TIMEOUT 1500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_HIT 300

#define PARAGOOMBA_STATE_SMALL_JUMP	400
#define PARAGOOMBA_STATE_FLY		500
#define PARAGOOMBA_STATE_NO_WING_WALKING	600

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay; 

	int hit_nx;
	ULONGLONG die_start;

	BOOLEAN isFellDown;
	BOOLEAN isOnPlatform;

	int trigger;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
	virtual int IsCollidable()
	{
		return (state != GOOMBA_STATE_HIT) && (state != GOOMBA_STATE_DIE) && isActived;
	}

};