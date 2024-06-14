#pragma once
#include "GameObject.h"
#include "Configs.h"

#define VENUS_BBOX_WIDTH 12
#define VENUS_BBOX_HEIGHT_TALL 28
#define VENUS_BBOX_HEIGHT_SHORT 20

#define VENUS_FIRE_RANGE 96

#define VENUS_STATE_HIDDEN 100
#define VENUS_STATE_UP 200
#define VENUS_STATE_DOWN 300
#define VENUS_STATE_FIRE 400
#define VENUS_STATE_DIE 500
#define VENUS_STATE_AIMING 600

#define VENUS_MOVE_SPEED 0.07f
#define VENUS_FIRE_NEAR 0.045f
#define VENUS_FIRE_FAR 0.02f

#define VENUS_FIRE_RANGE 72

#define VENUS_WAIT_TIME 1500
#define VENUS_SLEEP_TIME 3000

#define ID_ANI_VENUS_TALL_LEFT_UP 6002
#define ID_ANI_VENUS_TALL_LEFT_DOWN 6001
#define ID_ANI_VENUS_TALL_RIGHT_UP 6012
#define ID_ANI_VENUS_TALL_RIGHT_DOWN 6011

#define ID_ANI_VENUS_SHORT_LEFT_UP 6102
#define ID_ANI_VENUS_SHORT_LEFT_DOWN 6101
#define ID_ANI_VENUS_SHORT_RIGHT_UP 6112
#define ID_ANI_VENUS_SHORT_RIGHT_DOWN 6111

class CVenusPiranha : public CGameObject
{
	float hidden_y, grow_y;
	
	ULONGLONG wait_start;
	ULONGLONG sleep_start;
	int height;

	int GetTallID();
	int GetShortID();
public:
	CVenusPiranha(float x, float y, int height): CGameObject(x, y) {

		this->state = VENUS_STATE_HIDDEN;
		this->hidden_y = y ;
		this->grow_y = (height > 1) ? y - VENUS_BBOX_HEIGHT_TALL : y - VENUS_BBOX_HEIGHT_SHORT;
		this->vx = 0;
		this->vy = 0;
		this->height = height;
		wait_start = -1;
		sleep_start = -1;
		isActived = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	int IsBlocking() { return 0; }

	void StateHandler();

	void Reset();
};