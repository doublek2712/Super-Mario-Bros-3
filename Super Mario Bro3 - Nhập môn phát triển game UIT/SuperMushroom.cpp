#include "SuperMushroom.h"
#include "AssetIDs.h"
#include "Mario.h"
#include "Configs.h"
#include "ScoreData.h"

#include "debug.h"

CSuperMushroom::CSuperMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->def_y = y - GRID_SIZE;
	SetState(CONTAINED_STATE_DEACTIVE);
}

void CSuperMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - MUSHROOM_BBOX_WIDTH / 2;
		top = y - MUSHROOM_BBOX_HEIGHT / 2;
		right = left + MUSHROOM_BBOX_WIDTH;
		bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CSuperMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSuperMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking()) {
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
}

void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CONTAINED_STATE_DEACTIVE) return;
	if (state == CONTAINED_STATE_ACTIVE) {
		if(y <= def_y + GRID_SIZE - 2)
			SetState(MUSHROOM_STATE_COMEOUT);
	}
	else
	if (state == MUSHROOM_STATE_COMEOUT) {
		if (y <= def_y)
		{
			y = def_y;
			vy = 0;
			SetState(MUSHROOM_STATE_WALKING);
		}
	}
	else 
		vy += ay * dt;

	if ((state == MUSHROOM_STATE_DIE))
	{
		isDeleted = true;
		return;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CSuperMushroom::Render()
{
	if (state == CONTAINED_STATE_DEACTIVE || state == CONTAINED_STATE_ACTIVE) return;
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_POWERUP_MUSHROOM)->Draw(x, y);
	
	//RenderBoundingBox();
}

void CSuperMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONTAINED_STATE_ACTIVE:
		vy = -MUSHROOM_COMEOUT_SPEED;
		// add score
		
		break;
	case MUSHROOM_STATE_DIE:
		CGame::GetInstance()->GetData()->AddScore(SCORE_POWER_UP);
		vx = 0;
		vy = 0;
		ay = 0;
		isDeleted = true;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = -MUSHROOM_WALKING_SPEED;
		break;
	}

}

int CSuperMushroom::IsCollidable() {
	return (state != CONTAINED_STATE_DEACTIVE) && (state != CONTAINED_STATE_ACTIVE);
}
