#include "MarioOnWorldMap.h"
#include "Utils.h"

CMarioOnWorldMap::CMarioOnWorldMap(float x, float y) {
	this->x = x;
	this->y = y;
	this->stop_x = x;
	this->stop_y = y;
	this->vx = 0;
	this->vy = 0;
	this->level = MARIO_LVL_SMALL;
	SetState(MARIO_MAP_STATE_IDLE);
}

void CMarioOnWorldMap::Update(DWORD dt) {

	if (state == MARIO_MAP_STATE_IDLE) return; // ignore if idle

	x += vx * dt;
	y += vy * dt;

	switch (state)
	{
	case MARIO_MAP_STATE_WALKING_UP:
		if (y > stop_y) return;
		break;
	case MARIO_MAP_STATE_WALKING_DOWN:
		if (y < stop_y) return;
		break;
	case MARIO_MAP_STATE_WALKING_LEFT:
		if (x > stop_x) return;
		break;
	case MARIO_MAP_STATE_WALKING_RIGHT:
		if (x < stop_x) return;
		break;
	}

	x = stop_x;
	y = stop_y;
	vx = 0;
	vy = 0;
	SetState(MARIO_MAP_STATE_IDLE);
}
void CMarioOnWorldMap::Render() {
	int aniId = -1;

	if (state != MARIO_MAP_STATE_IDLE)
	{
		if (level == MARIO_LVL_SMALL)
			aniId = ID_ANI_MARIO_MAP_SMALL_WALK;
		else if (level == MARIO_LVL_BIG)
			aniId = ID_ANI_MARIO_MAP_BIG_WALK;
		else if (level == MARIO_LVL_RACCOON)
			aniId = ID_ANI_MARIO_MAP_RACCOON_WALK;
	}
	else
	{
		if (level == MARIO_LVL_SMALL)
			aniId = ID_ANI_MARIO_MAP_SMALL_IDLE;
		else if (level == MARIO_LVL_BIG)
			aniId = ID_ANI_MARIO_MAP_BIG_IDLE;
		else if (level == MARIO_LVL_RACCOON)
			aniId = ID_ANI_MARIO_MAP_RACCOON_IDLE;
	}


	if (aniId == -1)
		return;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CMarioOnWorldMap::SetState(int state) {

	switch (state)
	{
	case MARIO_MAP_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case MARIO_MAP_STATE_WALKING_UP:
		vy = -MARIO_ON_MAP_SPEED;
		break;
	case MARIO_MAP_STATE_WALKING_DOWN:
		vy = MARIO_ON_MAP_SPEED;
		break;
	case MARIO_MAP_STATE_WALKING_LEFT:
		vx = -MARIO_ON_MAP_SPEED;
		break;
	case MARIO_MAP_STATE_WALKING_RIGHT:
		vx = MARIO_ON_MAP_SPEED;
		break;
	}

	this->state = state;
}

void CMarioOnWorldMap::GoTo(float x, float y)
{
	if (x == this->x && y == this->y) return; // ignore if standing in place
	if (x == this->x) // go up/down
	{
		stop_y = y;
		if (this->y < stop_y)
			SetState(MARIO_MAP_STATE_WALKING_DOWN);
		else
			SetState(MARIO_MAP_STATE_WALKING_UP);
	}
	else if(y == this->y) // go to left/right
	{
		stop_x = x;
		if (this->x < stop_x)
			SetState(MARIO_MAP_STATE_WALKING_RIGHT);
		else
			SetState(MARIO_MAP_STATE_WALKING_LEFT);
	}
}