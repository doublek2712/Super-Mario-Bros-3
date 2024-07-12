#pragma once
#include "VenusPiranha.h"

#define PIRANHA_BBOX_WIDTH 12
#define PIRANHA_BBOX_HEIGHT_TALL 32
#define PIRANHA_BBOX_HEIGHT_SHORT 24

#define PIRANHA_STATE_HIDDEN 100
#define PIRANHA_STATE_UP 200
#define PIRANHA_STATE_DOWN 300
#define PIRANHA_STATE_DIE 500

#define PIRANHA_MOVE_SPEED (VENUS_MOVE_SPEED)

#define PIRANHA_SLEEP_TIME (VENUS_SLEEP_TIME)

#define ID_ANI_PIRANHA 6200

class CPiranha : public CGameObject
{
	float hidden_y, grow_y;

	ULONGLONG sleep_start;
	int height;

public:
	CPiranha(float x, float y, int height) : CGameObject(x, y) {

		this->state = PIRANHA_STATE_HIDDEN;
		this->hidden_y = y;
		this->grow_y = (height > 1) ? y - PIRANHA_BBOX_HEIGHT_TALL : y - PIRANHA_BBOX_HEIGHT_SHORT;
		this->vx = 0;
		this->vy = 0;
		this->height = height;
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