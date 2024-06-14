#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Block.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "FireBullet.h"
#include "VenusPiranha.h"
#include "Koopa.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isOnPlatform)
	{
		ay = MARIO_GRAVITY;
		isFlying = FALSE; 
	}
	else
		ay = MARIO_ON_AIR_DECLERATION;

	vy += ay * dt;
	vx += ax * dt;

	// deceleration to prevent slipping
	if (ax == 0 && vx != 0) {
		float deccel = (vx > 0) ? -MARIO_DECEL_WALK : MARIO_DECEL_WALK;
		if (deccel > 0)
			vx = min(vx + deccel * dt, 0);
		else
			vx = max(vx + deccel * dt, 0);
	}

	// switch state: walk -> run
	if (abs(vx) > abs(maxVx)) {
		vx = maxVx;
		if (state == MARIO_STATE_ACCEL_TO_RUN_RIGHT)
			SetState(MARIO_STATE_RUNNING_RIGHT);
		else if (state == MARIO_STATE_ACCEL_TO_RUN_LEFT)
			SetState(MARIO_STATE_RUNNING_LEFT);
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// reset kick timer 
	if (GetTickCount64() - kick_start > MARIO_KICK_ANI_TIME)
	{
		kick_start = 0;
		isKicking = FALSE;
	}
	// reset tail attack timer
	if (GetTickCount64() - tail_attack_start > MARIO_TAIL_ATTACK_TIME)
	{
		tail_attack_start = 0;
		isTailAttacking = FALSE;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (isHolding) {
		CKoopa* koopa = dynamic_cast<CKoopa*>(koopaShell);
		koopa->UpdatePositionFollowMario();
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBlock*>(e->obj))
		OnCollisionWithQBlock(e);
	else if (dynamic_cast<CSuperMushroom*>(e->obj))
		OnCollisionWithSuperMushroom(e);
	else if (dynamic_cast<CSuperLeaf*>(e->obj))
		OnCollisionWithSuperLeaf(e);
	else if (dynamic_cast<CFireBullet*>(e->obj))
		OnCollisionWithFire(e);
	else if (dynamic_cast<CVenusPiranha*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (koopa->GetState() == KOOPA_STATE_HELD) return;

	// jump on top >> 
	if (e->ny < 0)
	{
		if (koopa->GetState() == KOOPA_STATE_WALKING)
		{
			koopa->SetState(KOOPA_STATE_SHELL_IDLE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		if (koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
		{
			koopa->SetState(KOOPA_STATE_SHELL_MOVE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else 
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL_IDLE)
			{
				HitByEnemy();
			}
			else
			{
				if (readyToHold)
				{
					koopa->HoldByMario(&x, &y, &nx);
					koopaShell = koopa;
					SetState(MARIO_STATE_HOLDING);
				}
				else
				{
					SetState(MARIO_STATE_KICK);
					koopa->KickedByMario(nx);
				}

			}
		}
	}
}

void CMario::OnCollisionWithFire(LPCOLLISIONEVENT e) {

	HitByEnemy();

}
void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e) {

	HitByEnemy();

}
void CMario::OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e) {
	CSuperLeaf* leaf = dynamic_cast<CSuperLeaf*>(e->obj);

	if (leaf->IsCollidable()) {
		SetLevel(MARIO_LEVEL_RACCOON);
		leaf->SetState(LEAF_STATE_DIE);
	}

}
void CMario::OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e) {
	CSuperMushroom* mushroom = dynamic_cast<CSuperMushroom*>(e->obj);

	if (mushroom->IsCollidable()) {
		SetLevel(MARIO_LEVEL_BIG);
		mushroom->SetState(MUSHROOM_STATE_DIE);
	}

}
void CMario::OnCollisionWithQBlock(LPCOLLISIONEVENT e) {
	CBlock* block = dynamic_cast<CBlock*>(e->obj);
	//jump from below the block
	if(e->ny > 0)
	{ 
		if (block->GetState() == BLOCK_STATE_EMPTY)
			return;
		if (block->GetState() == BLOCK_STATE_IDLE) {
			block->SetState(BLOCK_STATE_COLLIDED);
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->IsCollidable())
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->IsCollidable())
			{
				HitByEnemy();
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsCollidable()) return;
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}
void CMario::HitByEnemy()
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_RACCOON)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			aniId = (nx > 0) ? ID_ANI_MARIO_SMALL_HOLD_RIGHT_JUMP : ID_ANI_MARIO_SMALL_HOLD_LEFT_JUMP;
		}
		else
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHolding)
				{
					aniId = (nx > 0) ? ID_ANI_MARIO_SMALL_HOLD_RIGHT_IDLE : ID_ANI_MARIO_SMALL_HOLD_LEFT_IDLE;
				}
				else
				if (isKicking)
				{
					aniId = (nx > 0) ? ID_ANI_MARIO_SMALL_KICK_RIGHT : ID_ANI_MARIO_SMALL_KICK_LEFT;
				}
				else
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT_WALKING;
				}
				else
				if (isKicking)
				{
					aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
				}
				else
				if (ax < 0 || nx < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_WALK_TO_RUN || ax == 0)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT_WALKING;
				}
				else
				if (isKicking)
				{
					aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
				}
				else
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_WALK_TO_RUN || ax == 0 )
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			aniId = (nx > 0) ? ID_ANI_MARIO_HOLD_RIGHT_JUMP : ID_ANI_MARIO_HOLD_LEFT_JUMP;
		}
		else
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHolding)
				{
					aniId = (nx > 0) ? ID_ANI_MARIO_HOLD_RIGHT_IDLE : ID_ANI_MARIO_HOLD_LEFT_IDLE;
				}
				else
				if (isKicking)
				{
					aniId = (nx > 0) ? ID_ANI_MARIO_KICK_RIGHT : ID_ANI_MARIO_KICK_LEFT;
				}
				else
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_HOLD_RIGHT_WALKING;
				}
				else
				if (isKicking)
				{
					aniId = ID_ANI_MARIO_KICK_RIGHT;
				}
				else
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_WALK_TO_RUN || ax == 0)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_HOLD_LEFT_WALKING;
				}
				else
				if (isKicking)
				{
					aniId = ID_ANI_MARIO_KICK_LEFT;
				}
				else
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_WALK_TO_RUN || ax == 0)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for raccoon Mario
//
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (isTailAttacking)
	{
		aniId = (nx > 0) ? ID_ANI_MARIO_RACCOON_TAIL_ATTACK_RIGHT : ID_ANI_MARIO_RACCOON_TAIL_ATTACK_LEFT;
	}
	else
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			aniId = (nx > 0) ? ID_ANI_MARIO_RACCOON_HOLD_RIGHT_JUMP : ID_ANI_MARIO_RACCOON_HOLD_LEFT_JUMP;
		}
		else
		if (isWagging)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_TAIL_WAGGING_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_TAIL_WAGGING_LEFT;
		}
		else
		if (isFlying)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_FLY_TAIL_WAGGING_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_FLY_TAIL_WAGGING_LEFT;
		}
		else
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy < 0)
				aniId = (nx >= 0) ? ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT : ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			else
				aniId = (nx >= 0) ? ID_ANI_MARIO_RACCOON_JUMP_FALLING_RIGHT : ID_ANI_MARIO_RACCOON_JUMP_FALLING_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHolding)
				{
					aniId = (nx > 0) ? ID_ANI_MARIO_RACCOON_HOLD_RIGHT_IDLE : ID_ANI_MARIO_RACCOON_HOLD_LEFT_IDLE;
				}
				else
				if (isKicking)
				{
					aniId = (nx > 0) ? ID_ANI_MARIO_RACCOON_KICK_RIGHT : ID_ANI_MARIO_RACCOON_KICK_LEFT;
				}
				else 
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_RACCOON_HOLD_RIGHT_WALKING;
				}
				else
				if (isKicking)
				{
					aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
				}
				else
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_ACCEL_WALK_TO_RUN || ax == 0)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_RACCOON_HOLD_LEFT_WALKING;
				}
				else
				if (isKicking)
				{
					aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
				}
				else
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_ACCEL_WALK_TO_RUN || ax == 0)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);


	//DebugOutTitle(L"Coins: %d. x = %f, y = %f", coin, x, y);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) return;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) return;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) return;
		if (vx < 0 && -vx > MARIO_WALKING_SPEED)
		{
			maxVx = MARIO_RUNNING_SPEED;
			ax = MARIO_DECEL_RUN;
		}
		else
		{
			maxVx = MARIO_WALKING_SPEED;
			ax = MARIO_ACCEL_WALK_X;
		}
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) return;
		if (vx > 0 && -vx < -MARIO_WALKING_SPEED)
		{
			maxVx = -MARIO_RUNNING_SPEED;
			ax = -MARIO_DECEL_RUN;
		}
		else
		{
			maxVx = -MARIO_WALKING_SPEED;
			ax = -MARIO_ACCEL_WALK_X;
		}

		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) return;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else if (abs(this->vx) == MARIO_RUNNING_SPEED && level == MARIO_LEVEL_RACCOON)
		{
			isFlying = TRUE;
			vy = -MARIO_JUMP_RUN_SPEED_Y;
		}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			isWagging = TRUE;
			vy = -MARIO_WAGGING_FALL_SPEED;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 3;
		isFlying = FALSE;
		isWagging = FALSE;
		break;

	case MARIO_STATE_SIT:
		if (vx != 0) return;
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_KICK:
		if (isSitting) return;
		isKicking = TRUE;
		kick_start = GetTickCount64();
		break;
	case MARIO_STATE_READY_TO_HOLD:
		readyToHold = TRUE;
		break;
	case MARIO_STATE_HOLDING:
		readyToHold = FALSE;
		isHolding = TRUE;
		break;

	case MARIO_STATE_RELEASE_HOLD:
		if (isHolding)
		{
			isHolding = FALSE;
			CKoopa* koopa = dynamic_cast<CKoopa*>(koopaShell);
			SetState(MARIO_STATE_KICK);
			koopa->KickedByMario(nx);
			koopaShell = nullptr;
		}
		break;

	case MARIO_STATE_ACCEL_TO_RUN_LEFT:
		if (isSitting) return;
		maxVx = -MARIO_RUNNING_SPEED;
		if (vx <= 0)
			ax = -MARIO_ACCEL_WALK_TO_RUN;
		else
			ax = -MARIO_DECEL_RUN;
		nx = -1;
		break;

	case MARIO_STATE_ACCEL_TO_RUN_RIGHT:
		if (isSitting) return;
		maxVx = MARIO_RUNNING_SPEED;
		if (vx >= 0)
			ax = MARIO_ACCEL_WALK_TO_RUN;
		else
			ax = MARIO_DECEL_RUN;
		nx = 1;
		break;

	case MARIO_STATE_TAIL_ATTACK:
		isTailAttacking = TRUE;
		tail_attack_start = GetTickCount64();
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		//vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}

	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

int CMario::GetLevel()
{
	return this->level;
}

