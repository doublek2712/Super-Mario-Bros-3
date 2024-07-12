#pragma once
#include "GameObject.h"

#define MARIO_ON_MAP_SPEED	0.05f


#define ID_ANI_MARIO_MAP_BIG_IDLE		3002
#define ID_ANI_MARIO_MAP_SMALL_IDLE		3001
#define ID_ANI_MARIO_MAP_RACCOON_IDLE	3003

#define ID_ANI_MARIO_MAP_BIG_WALK		3012
#define ID_ANI_MARIO_MAP_SMALL_WALK		3011
#define ID_ANI_MARIO_MAP_RACCOON_WALK	3013

#define MARIO_LVL_BIG		2
#define MARIO_LVL_SMALL		1
#define MARIO_LVL_RACCOON	3

#define MARIO_MAP_STATE_IDLE	100
#define MARIO_MAP_STATE_WALKING_UP		201
#define MARIO_MAP_STATE_WALKING_DOWN	202
#define MARIO_MAP_STATE_WALKING_LEFT	203
#define MARIO_MAP_STATE_WALKING_RIGHT	204

class CMarioOnWorldMap
{
	float x;
	float y;
	float vy, vx;
	float stop_x, stop_y;

	int level;
	int state;

	
public:
	CMarioOnWorldMap(float x, float y);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; };
	void SetPosition(float x, float y) { 
		this->x = x; 
		this->y = y; 
		this->stop_x = x;
		this->stop_y = y;
	}
	void GoTo(float x, float y);
};
