#include "Goomba.h"
#include "debug.h"
#include "AssetIDs.h"
#include "PlayScene.h"
CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	hit_nx = 0;
	isActived = false;
	isFellDown = false;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// preprocessing
	// process when camera enter , stay or leave
	if (!CGame::GetInstance()->IsCamEnter(def_x, def_y)) {
		if (!isActived)
		{
			trigger = TRIGGER_READY;
			if (CGame::GetInstance()->IsRightSideOfCam(def_x))
				vx = -GOOMBA_WALKING_SPEED;
			else
				vx = GOOMBA_WALKING_SPEED;
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


	// process when goomba falls off the scene
	CPlayScene* scene = dynamic_cast<CPlayScene*>( CGame::GetInstance()->GetCurrentScene() );
	if (scene->IsFallOff(y))
	{
		isActived = false;
		x = def_x;
		y = def_y;
		return;
	}

	//
	if ( ((state==GOOMBA_STATE_DIE) || (state == GOOMBA_STATE_HIT)) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	if (!isActived) return;
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	if (state == GOOMBA_STATE_HIT)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_GOOMBA_WALK_1)->Draw(x, y, /*flipX*/TRUE);
	}
	else
		CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_HIT:
			die_start = GetTickCount64();
			vy = -GOOMBA_HIT_DEFLECT_SPEED;
			break;
	}
}


