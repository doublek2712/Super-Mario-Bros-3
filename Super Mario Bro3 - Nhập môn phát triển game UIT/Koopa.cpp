#include "Koopa.h"
#include "debug.h"
#include "Platform.h"
#include "Ground.h"
#include "Block.h"
#include "Mario.h"
#include "Goomba.h"
#include "VenusPiranha.h"
#include "Wood.h"
#include "PlayScene.h"
#include "ParaKoopa.h"
#include "Brick.h"

int RelativedPositionOfPlatformChecker(int x, int nx) {
	return x + nx * (KOOPA_BBOX_WIDTH - 4);
}

CKoopa::CKoopa(float x, float y, BOOLEAN block) :CGameObject(x, y)
{
	this->ax = 0;
	this->isBlockByPlatform = block;
	this->ay = KOOPA_GRAVITY;
	this->nx = -1;
	this->m_x = nullptr;
	this->m_y = nullptr;
	this->isHeld = FALSE;
	this->isKicked = FALSE;

	if (block)
	{
		platformChecker = new CPlatformChecker(RelativedPositionOfPlatformChecker(x, nx), y, KOOPA_BBOX_HEIGHT, KOOPA_BBOX_WIDTH);
	}
	else platformChecker = nullptr;

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
	
	if (dynamic_cast<CBlock*>(e->obj))
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
	
}
void CKoopa::OnCollisionWithBlock(LPCOLLISIONEVENT e)
{
	if (e->nx != 0)
	{
		if (dynamic_cast<CWood*>(e->obj))
			return;
		if (dynamic_cast<CBrick*>(e->obj))
		{
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			if (brick->GetState() == BRICK_STATE_IDLE && isKicked)
					brick->SetState(BRICK_STATE_HIT);
		}
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

	// process when koopa falls off the scene
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene->IsFallOff(y))
	{
		isActived = false;
		x = def_x;
		y = def_y;
		if (dynamic_cast<CParaKoopa*>(this))
			SetState(PARAKOOPA_STATE_FLY);
		else
		SetState(KOOPA_STATE_WALKING);
		return;
	}

	if (isBlockByPlatform && state == KOOPA_STATE_WALKING)
	{

	}

	if (state == KOOPA_STATE_SHELL_IDLE_HIT)
	{
		if (isOnPlatform)
			SetState(KOOPA_STATE_SHELL_IDLE);
	}

	//
	if (platformChecker != nullptr)
	{
		platformChecker->Update(dt, coObjects);
		if (platformChecker->IsFallOffPlatform() && isBlockByPlatform && state == KOOPA_STATE_WALKING && isOnPlatform)
		{
			vx = -vx;
			nx = -nx;

			platformChecker->SetVx(vx);
			platformChecker->SetPosition(RelativedPositionOfPlatformChecker(x, nx), y);
		}

	}
	

	isOnPlatform = false;

	if(!isHeld)
		CCollision::GetInstance()->Process(this, dt, coObjects);
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
		if (platformChecker != nullptr)
		{
			platformChecker->SetVx(vx);
		}
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