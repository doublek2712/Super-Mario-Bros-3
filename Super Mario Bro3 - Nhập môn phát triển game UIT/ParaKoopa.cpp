#include "ParaKoopa.h"

CParaKoopa::CParaKoopa(float x, float y, BOOLEAN block) : CKoopa(x, y, block)
{
	SetState(PARAKOOPA_STATE_FLY);
}
void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CKoopa::Update(dt, coObjects);

	if (state == PARAKOOPA_STATE_FLY)
	{
		if (isOnPlatform)
		{
			SetState(PARAKOOPA_STATE_FLY);
		}
	}
}

void CParaKoopa::Render()
{
	if (!isActived) return;

	int aniId = -1;
	if (state != PARAKOOPA_STATE_FLY) {
		aniId = (vx < 0) ? ID_ANI_KOOPA_GREEN_WALKING_LEFT : ID_ANI_KOOPA_GREEN_WALKING_RIGHT;
		if (state == KOOPA_STATE_SHELL_IDLE ||
			state == KOOPA_STATE_HELD ||
			state == KOOPA_STATE_HIT ||
			state == KOOPA_STATE_SHELL_IDLE_HIT)
			aniId = ID_ANI_KOOPA_GREEN_SHELL_IDLE;
		else
			if (state == KOOPA_STATE_SHELL_MOVE)
				aniId = ID_ANI_KOOPA_GREEN_SHELL_MOVE;
	}
	else
	{
		aniId = (vx < 0) ? ID_ANI_PARAKOOPA_GREEN_WALKING_LEFT : ID_ANI_PARAKOOPA_GREEN_WALKING_RIGHT;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int bboxHeight;
	if (state == PARAKOOPA_STATE_FLY || state == KOOPA_STATE_WALKING)
		bboxHeight = KOOPA_BBOX_HEIGHT;
	else
		bboxHeight = KOOPA_SHELL_BBOX_HEIGHT;
	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - bboxHeight / 2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + bboxHeight;

}

void CParaKoopa::SetState(int state)
{
	switch (state)
	{
	case PARAKOOPA_STATE_FLY:
		vy = -PARAKOOPA_FLY_SPEED;
		vx = nx * KOOPA_WALKING_SPEED;
		isOnPlatform = FALSE;
		break;

	}

	CKoopa::SetState(state);

}