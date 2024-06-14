#include "Koopa.h"
#include "debug.h"
#include "Platform.h"
#include "Ground.h"
#include "Block.h"
#include "Mario.h"
#include "Goomba.h"
#include "VenusPiranha.h"
#include "Wood.h"
CKoopa::CKoopa(float x, float y, BOOLEAN block) :CGameObject(x, y)
{
	this->ax = 0;
	this->isBlockByPlatform = block;
	this->ay = KOOPA_GRAVITY;
	this->isOnBlock = FALSE;
	this->nx = -1;
	this->m_x = nullptr;
	this->m_y = nullptr;
	this->isHeld = FALSE;
	this->isKicked = FALSE;
	SetState(KOOPA_STATE_WALKING);
}


void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int bboxHeight = (state == KOOPA_STATE_WALKING) ? KOOPA_BBOX_HEIGHT : KOOPA_SHELL_BBOX_HEIGHT;
	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - bboxHeight / 2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + bboxHeight;

}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) {
		OnCollisionWithOtherUnit(e);
		return;
	}
	
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
		}

	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
	if (dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CGround*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CBlock*>(e->obj))
		OnCollisionWithBlock(e);
		
	
}
void CKoopa::OnCollisionWithOtherUnit(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVE)
	{
		if (dynamic_cast<CMario*>(e->obj))
		{
			CMario* mario = dynamic_cast<CMario*>(e->obj);
			mario->HitByEnemy();
		}
		else if (dynamic_cast<CGoomba*>(e->obj))
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			goomba->SetState(GOOMBA_STATE_HIT);
		}
		else if (dynamic_cast<CKoopa*>(e->obj) )
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
			koopa->GetHit(nx);
		}
	}
	
}

void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		isOnBlock = FALSE;
		CGameObject* platform = e->obj;

		float l, r, t, b;
		platform->GetBoundingBox(l, t, r, b);

		l_bounded = l;
		r_bounded = r;
	}
	
}
void CKoopa::OnCollisionWithBlock(LPCOLLISIONEVENT e)
{
	
	if (e->ny < 0)
	{
		

		float l, r, t, b;
		e->obj->GetBoundingBox(l, t, r, b);
		//DebugOut(L"%f\n", r);
		if (!isOnBlock)
		{
			l_bounded = l;
			r_bounded = r;
			isOnBlock = TRUE;
		}
		else
		{
			l_bounded = min(l, l_bounded);
			r_bounded = max(r, r_bounded);

		}
	}
	else if (e->nx != 0)
	{
		if (dynamic_cast<CWood*>(e->obj))
			return;

		CBlock* block = dynamic_cast<CBlock*>(e->obj);
		if(isKicked)
			block->SetState(BLOCK_STATE_COLLIDED_SIDE);
	}
	
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// preprocessing
	// process when camera enter , stay or leave
	if (!CGame::GetInstance()->IsCamEnter(def_x, def_y)) {
		if (!isActived)
		{
			trigger = TRIGGER_READY;
			if (CGame::GetInstance()->IsRightSideOfCam(def_x))
				vx = -KOOPA_WALKING_SPEED;
			else
				vx = KOOPA_WALKING_SPEED;
		}
	}
	else if (trigger == TRIGGER_READY)
	{
		trigger = TRIGGER_TRIGGER;
	}


	if (!isActived && trigger == TRIGGER_TRIGGER)
	{
		isActived = true;
		trigger = TRIGGER_IGNORE; // that mean the camera stay and then we don't want trigger anymore
	}

	// 
	if (!isActived) return;

	vy += ay * dt;
	vx += ax * dt;

	if (isBlockByPlatform && state == KOOPA_STATE_WALKING)
	{
		if ((x <= l_bounded && vx < 0) || (x >= r_bounded && vx > 0))
		{
			vx = -vx;
			nx = -nx;
		}
	}

	if (state == KOOPA_STATE_SHELL_IDLE_HIT)
	{
		if (isOnPlatform)
			SetState(KOOPA_STATE_SHELL_IDLE);
	}

	isOnPlatform = false;

	if(!isHeld)
		CCollision::GetInstance()->Process(this, dt, coObjects, 1);
	else {
		
	}
}


void CKoopa::Render()
{
	if (!isActived) return;

	int aniId = -1;
	if (isBlockByPlatform) {
		aniId = (vx < 0) ? ID_ANI_KOOPA_RED_WALKING_LEFT : ID_ANI_KOOPA_RED_WALKING_RIGHT;
		if (state == KOOPA_STATE_SHELL_IDLE || 
			state == KOOPA_STATE_HELD || 
			state == KOOPA_STATE_HIT ||
			state == KOOPA_STATE_SHELL_IDLE_HIT)
			aniId = ID_ANI_KOOPA_RED_SHELL_IDLE;
		else 
		if (state == KOOPA_STATE_SHELL_MOVE)
			aniId = ID_ANI_KOOPA_RED_SHELL_MOVE;
	}
	else
	{
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
	

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		vx = nx * KOOPA_WALKING_SPEED;
		isKicked = FALSE;
		break;
	case KOOPA_STATE_SHELL_IDLE:
		vx = 0;
		break;
	case KOOPA_STATE_SHELL_MOVE:
		isHeld = FALSE;
		m_x = nullptr;
		m_y = nullptr;
		m_nx = nullptr;
		vx = nx*KOOPA_SHELL_MOVE;
		break;
	case KOOPA_STATE_HELD:
		isHeld = TRUE;
		break;
	case KOOPA_STATE_HIT:
		vy = -KOOMBA_HIT_DEFLECT_SPEED;
		vx = nx * KOOPA_WALKING_SPEED;
		isOnPlatform = FALSE;
		SetState(KOOPA_STATE_SHELL_IDLE_HIT);
		break;
	}
}

void CKoopa::KickedByMario(int nx)
{
	this->nx = nx;
	isKicked = TRUE;
	SetState(KOOPA_STATE_SHELL_MOVE);
}
void CKoopa::GetHit(int nx)
{
	this->nx = nx;
	SetState(KOOPA_STATE_HIT);
}

void CKoopa::HoldByMario(float* x, float* y, int* nx)
{
	m_x = x;
	m_y = y;
	m_nx = nx;
	SetState(KOOPA_STATE_HELD);
}

void CKoopa::UpdatePositionFollowMario()
{
	if (isHeld)
	{
		x = *m_x + *m_nx * (KOOPA_BBOX_WIDTH / 2 + 4);
		y = *m_y - 1;
	}
}