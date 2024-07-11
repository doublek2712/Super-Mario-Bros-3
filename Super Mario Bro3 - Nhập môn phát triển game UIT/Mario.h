#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.19f
#define MARIO_PIPE_SPEED		0.05f

#define MARIO_RUNNING_SPEED_STEP	0.015

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_ACCEL_WALK_TO_RUN	(MARIO_ACCEL_WALK_X)

#define MARIO_DECEL_WALK	0.00025f
#define MARIO_DECEL_RUN	(MARIO_DECEL_WALK*2)

#define MARIO_JUMP_SPEED_Y			0.3f
#define MARIO_JUMP_RUN_SPEED_Y		0.33f
#define MARIO_JUMP_DEFLECT_SPEED	0.2f
#define MARIO_FLY_SPEED				0.25f

#define MARIO_WAGGING_FALL_SPEED	0.01f

#define MARIO_GRAVITY					0.002f
#define MARIO_ON_AIR_DECLERATION		0.0005f

#pragma region MARIO_STATE_ID

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICK			700

#define MARIO_STATE_READY_TO_HOLD	800
#define MARIO_STATE_HOLDING			801
#define MARIO_STATE_RELEASE_HOLD	802

#define MARIO_STATE_ACCEL_TO_RUN_LEFT	900
#define MARIO_STATE_ACCEL_TO_RUN_RIGHT	901

#define MARIO_STATE_TAIL_ATTACK		1000

#define MARIO_STATE_PIPE_ENTRANCE	1101
#define MARIO_STATE_PIPE_EXIT		1102
#define MARIO_STATE_UP				1200

#pragma endregion

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT 1010
#define ID_ANI_MARIO_KICK_LEFT 1011

#define ID_ANI_MARIO_HOLD_LEFT_IDLE 1020
#define ID_ANI_MARIO_HOLD_LEFT_WALKING 1021
#define ID_ANI_MARIO_HOLD_LEFT_JUMP 1030

#define ID_ANI_MARIO_HOLD_RIGHT_IDLE 1025
#define ID_ANI_MARIO_HOLD_RIGHT_WALKING 1026
#define ID_ANI_MARIO_HOLD_RIGHT_JUMP 1031

#define	ID_ANI_MARIO_TURN_INTO_SMALL_LEFT	1040
#define	ID_ANI_MARIO_TURN_INTO_SMALL_RIGHT	1041

#define ID_ANI_MARIO_PIPE	1050

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1610
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1611

#define ID_ANI_MARIO_SMALL_HOLD_LEFT_IDLE 1620
#define ID_ANI_MARIO_SMALL_HOLD_LEFT_WALKING 1621
#define ID_ANI_MARIO_SMALL_HOLD_LEFT_JUMP 1630

#define ID_ANI_MARIO_SMALL_HOLD_RIGHT_IDLE 1625
#define ID_ANI_MARIO_SMALL_HOLD_RIGHT_WALKING 1626
#define ID_ANI_MARIO_SMALL_HOLD_RIGHT_JUMP 1631

#define	ID_ANI_MARIO_SMALL_TURN_INTO_BIG_LEFT	1640
#define	ID_ANI_MARIO_SMALL_TURN_INTO_BIG_RIGHT	1641

#define ID_ANI_MARIO_SMALL_PIPE	1650

// RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2000
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2001
#define ID_ANI_MARIO_RACCOON_JUMP_FALLING_RIGHT 2010
#define ID_ANI_MARIO_RACCOON_JUMP_FALLING_LEFT 2011
#define ID_ANI_MARIO_RACCOON_TAIL_WAGGING_RIGHT 2020
#define ID_ANI_MARIO_RACCOON_TAIL_WAGGING_LEFT 2021

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2101
#define ID_ANI_MARIO_RACCOON_FLY_TAIL_WAGGING_RIGHT 2110
#define ID_ANI_MARIO_RACCOON_FLY_TAIL_WAGGING_LEFT 2111

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2201

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 2310
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 2311

#define ID_ANI_MARIO_RACCOON_HOLD_LEFT_IDLE 2320
#define ID_ANI_MARIO_RACCOON_HOLD_LEFT_WALKING 2321
#define ID_ANI_MARIO_RACCOON_HOLD_LEFT_JUMP 2330

#define ID_ANI_MARIO_RACCOON_HOLD_RIGHT_IDLE 2325
#define ID_ANI_MARIO_RACCOON_HOLD_RIGHT_WALKING 2326
#define ID_ANI_MARIO_RACCOON_HOLD_RIGHT_JUMP 2331

#define ID_ANI_MARIO_RACCOON_TAIL_ATTACK_LEFT 2401
#define ID_ANI_MARIO_RACCOON_TAIL_ATTACK_RIGHT 2402

#define ID_ANI_MARIO_RACCOON_PIPE	2500

#define ID_ANI_MARIO_TURN_INTO_RACCOON	13000
#define ID_ANI_MARIO_RACCOON_TURN_INTO_BIG	13000

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  10
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  7
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_RACCOON_TAIL_ATTACK_WIDTH	24

#define MARIO_UNTOUCHABLE_TIME	3000
#define MARIO_KICK_ANI_TIME		300
#define MARIO_TAIL_ATTACK_TIME	400
#define MARIO_TRANSFORM_TIME	600
#define MARIO_PIPE_TIME			800

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int previous_level;
	int untouchable;

	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG tail_attack_start;
	ULONGLONG transform_start;
	ULONGLONG pipe_start;

	BOOLEAN readyToHold;
	BOOLEAN readyToPipe;

	int pipeDestination;
	float pipeDestination_x;
	int pipeDestination_ny;
	int mapIndex; // -1 is default

	BOOLEAN isOnPlatform;
	BOOLEAN isHolding;
	BOOLEAN isKicking;
	BOOLEAN isFlying;
	BOOLEAN isWagging;
	BOOLEAN isTailAttacking;
	BOOLEAN isTransform;
	BOOLEAN isPipe;

	CGameObject* koopaShell;

	void OnCollisionWithFire(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithQBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);

	int GetAniIdRaccoon();
	int GetAniIdBig();
	int GetAniIdSmall();


public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		level = MARIO_LEVEL_SMALL;
		previous_level = level;

		untouchable = 0;
		untouchable_start = 0;
		kick_start = 0;
		tail_attack_start = 0;
		transform_start = 0;

		readyToHold = FALSE;
		readyToPipe = FALSE;

		pipeDestination = -1;
		pipeDestination_x = -1;
		pipeDestination_ny = 0;
		mapIndex = -1;

		isOnPlatform = FALSE;
		isKicking = FALSE;
		isHolding = FALSE;
		isFlying = FALSE;
		isWagging = FALSE;
		isTailAttacking = FALSE;
		isTransform = FALSE;
		isPipe = FALSE;

		koopaShell = nullptr;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return 
			(state != MARIO_STATE_DIE) 
			&& (!isPipe)
			&& (!isTransform);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void HitByEnemy();

	BOOLEAN IsFlying() { return isFlying; }
	BOOLEAN IsPipe() { return isPipe; }
	
	int GetPipeDestination() { return pipeDestination;  }
	int GetMap() { return mapIndex; }
};