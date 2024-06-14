#include "VenusPiranha.h"
#include "PlayScene.h"
#include "FireBullet.h"
#include "AssetIDs.h"
#include "debug.h"

void CVenusPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	float cx, cy;
	game->GetCamPos(cx, cy);

	float sw, sh;
	game->GetScreenSize(sw, sh);

	y += vy * dt;

	StateHandler();

	if (IsCamEnter() && isTrigger == false)
	{
		if (state == VENUS_STATE_HIDDEN && GetTickCount64() - sleep_start > VENUS_SLEEP_TIME)
		{
			sleep_start = -1;
			isTrigger = true;
			SetState(VENUS_STATE_UP);
		}
	}
	if (!IsCamEnter() && isTrigger == true)
	{
		isTrigger = false;
	}
	if (GetTickCount64() - sleep_start > VENUS_SLEEP_TIME)
	{
		sleep_start = -1;
		if (state == VENUS_STATE_HIDDEN && isTrigger)
			SetState(VENUS_STATE_UP);
	}
	if (GetTickCount64() - wait_start > VENUS_WAIT_TIME)
	{
		wait_start = -1;
		if (state == VENUS_STATE_AIMING)
			SetState(VENUS_STATE_FIRE);
	}
	if (state == VENUS_STATE_FIRE)
	{
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CMario* player = (CMario*)scene->GetPlayer();
		float px, py;
		player->GetPosition(px, py);
		bool face_left = px <= this->x;
		bool face_up = py <= this->y;

		float vx = (face_left) ? -1 : 1;
		float vy = (face_up) ? -1 : 1;

		if( (face_left && px >= this->x - VENUS_FIRE_RANGE) ||
			(!face_left && px <= this->x + VENUS_FIRE_RANGE)
		)
		{
			vx *= VENUS_FIRE_NEAR;
			vy *= VENUS_FIRE_NEAR;
		}
		else 
		{
			vx *= VENUS_FIRE_NEAR;
			vy *= VENUS_FIRE_FAR;
		}
		CFireBullet* fire = new CFireBullet(x, y, vx, vy);
		scene->SpawnObject(fire);
		SetState(VENUS_STATE_DOWN);
	}
		

}
void CVenusPiranha::Reset()
{
	this->vx = 0;
	this->vy = 0;
	wait_start = -1;
	sleep_start = -1;
	isTrigger = false;
	y = hidden_y;
}
void CVenusPiranha::StateHandler() 
{
	if (y <= grow_y && state == VENUS_STATE_UP)
	{
		y = grow_y;
		vy = 0;
		SetState(VENUS_STATE_AIMING);
	}
	else
	if (y >= hidden_y && state == VENUS_STATE_DOWN)
	{
		y = hidden_y;
		vy = 0;
		SetState(VENUS_STATE_HIDDEN);
	}
}

void CVenusPiranha::Render()
{

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();
	float px, py;
	player->GetPosition(px, py);

	bool face_left = px <= this->x;
	bool face_up = py <= this->y;

	if (state == VENUS_STATE_AIMING)
	{
		CPlayScene* scene = (CPlayScene*) CGame::GetInstance()->GetCurrentScene();
		CMario* player = (CMario*)scene->GetPlayer();
		float px, py;
		player->GetPosition(px, py);

		CSprites* sprites = CSprites::GetInstance();
		int spriteID = -1;

		if (face_left) {
			if (face_up)
				spriteID = (height>1) ? ID_SPRITE_VENUS_TALL_LEFT_UP_OPEN : ID_SPRITE_VENUS_SHORT_LEFT_UP_OPEN;
			else 
				spriteID = (height > 1) ? ID_SPRITE_VENUS_TALL_LEFT_DOWN_OPEN : ID_SPRITE_VENUS_SHORT_LEFT_DOWN_OPEN;
		}
		else
		{
			if (face_up)
				spriteID = (height > 1) ? ID_SPRITE_VENUS_TALL_RIGHT_UP_OPEN : ID_SPRITE_VENUS_SHORT_RIGHT_UP_OPEN;
			else
				spriteID = (height > 1) ? ID_SPRITE_VENUS_TALL_RIGHT_DOWN_OPEN : ID_SPRITE_VENUS_SHORT_RIGHT_DOWN_OPEN;
		}

		sprites->Get(spriteID)->Draw(x, y);
	}
	else
	{
		CAnimations* s = CAnimations::GetInstance();
		int aniID = -1;
		if (face_left)
			aniID = (height > 1) ? ID_ANI_VENUS_TALL_LEFT_UP : ID_ANI_VENUS_SHORT_LEFT_UP;
		else
			aniID = (height > 1) ? ID_ANI_VENUS_TALL_RIGHT_UP : ID_ANI_VENUS_SHORT_RIGHT_UP;
		s->Get(aniID)->Render(x, y);
	}

	//RenderBoundingBox();
}

	

void CVenusPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float bbheight = (height > 1) ? VENUS_BBOX_HEIGHT_TALL : VENUS_BBOX_HEIGHT_SHORT;
	l = x - VENUS_BBOX_WIDTH / 2;
	t = y - bbheight / 2;
	r = l + VENUS_BBOX_WIDTH;
	b = t + bbheight;
}
void CVenusPiranha::SetState(int state)
{
	switch (state)
	{
	case VENUS_STATE_UP:
		vy = -VENUS_MOVE_SPEED;
		break;
	case VENUS_STATE_DOWN:
		vy = VENUS_MOVE_SPEED;
		break;
	case VENUS_STATE_HIDDEN:
		sleep_start = GetTickCount64();
		break;
	case VENUS_STATE_FIRE:
		break;
	case VENUS_STATE_DIE:
		break;
	case VENUS_STATE_AIMING:
		wait_start = GetTickCount64();
		break;
	}

	CGameObject::SetState(state);
}