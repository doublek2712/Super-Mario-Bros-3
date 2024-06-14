#include "debug.h"
#include "ParaGoomba.h"
#include "AssetIDs.h"

CParaGoomba::CParaGoomba(float x, float y) : CGoomba(x, y)
{
	numOfJumps = 0;
	isJump = FALSE;
	walk_start = 0;
	isFlying = FALSE;
}
void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGoomba::Update(dt, coObjects);

	if (state != PARAGOOMBA_STATE_NO_WING_WALKING)
	{
		if (isJump && isOnPlatform && (numOfJumps < PARAGOOMBA_SMALL_JUMP_MAX))
		{
			vy = -PARAGOOMBA_SMALL_JUMP_SPEED;
			numOfJumps++;
		}

		if (numOfJumps == PARAGOOMBA_SMALL_JUMP_MAX && isJump)
		{
			isJump = FALSE;
			numOfJumps = 0;
			SetState(PARAGOOMBA_STATE_FLY);

		}

		if (isFlying && isOnPlatform)
		{
			isFlying = FALSE;
			walk_start = GetTickCount64();
			SetState(GOOMBA_STATE_WALKING);
		}

		if (GetTickCount64() - walk_start > PARAGOOMBA_WALK_TIMEOUT)
		{
			walk_start = 0;
			if (state == GOOMBA_STATE_WALKING)
				SetState(PARAGOOMBA_STATE_SMALL_JUMP);
		}
	}
}

void CParaGoomba::Render()
{
	if (!isActived) return;
	int aniId = ID_ANI_PARAGOOMBA_WALKING_CLOSE_WING;

		switch (state)
		{
		case GOOMBA_STATE_DIE:
			aniId = ID_ANI_PARAGOOMBA_DIE;
			break;
		case PARAGOOMBA_STATE_SMALL_JUMP:
			aniId = ID_ANI_PARAGOOMBA_SMALL_JUMP;
			break;
		case PARAGOOMBA_STATE_FLY:
			aniId = ID_ANI_PARAGOOMBA_FLY;
			break;
		case PARAGOOMBA_STATE_NO_WING_WALKING:
			aniId = ID_ANI_PARAGOOMBA_NO_WING_WALK;
			break;
		}



	if (state == GOOMBA_STATE_HIT)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_PARAGOOMBA_NO_WING_WALK_1)->Draw(x, y, /*flipX*/TRUE);
	}
	else
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		float bufferHeight = (state == PARAGOOMBA_STATE_NO_WING_WALKING) ? 0 : PARAGOOMBA_BBOX_BUFFER_HEIGHT/2;
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2 + bufferHeight;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::SetState(int state)
{
	switch (state)
	{
	case PARAGOOMBA_STATE_SMALL_JUMP:
		isJump = TRUE;
		break;
	case PARAGOOMBA_STATE_FLY:
		isFlying = TRUE;
		vy = -PARAGOOMBA_FLY_SPEED;
		isOnPlatform = FALSE;
		break;
	case PARAGOOMBA_STATE_NO_WING_WALKING:
		vx = nx * GOOMBA_WALKING_SPEED;
		break;
	}

	CGoomba::SetState(state);

}
