#pragma once
#include "Game.h"
#include "ScoreData.h"

#define EFFECT_SCORE_SPEED	0.14f

#define EFFECT_ID_SCORE_100		(SCORE_ENEMY)
#define EFFECT_ID_SCORE_1000	(SCORE_POWER_UP)
#define EFFECT_ID_BRICK_BROKEN	-1000

#define ID_ANI_SCORE_100	14001
#define ID_ANI_SCORE_1000	14002

#define ID_ANI_BRICK_BROKEN_LEFT	15001
#define ID_ANI_BRICK_BROKEN_RIGHT	15002

#define EFFECT_SCORE_TIME	500

class CEffect
{
	float x, y;
	int effect_id;
	ULONGLONG effect_start;
	BOOLEAN isDeleted;
public:
	CEffect(float x, float y, int effect_id) {
		this->x = x;
		this->y = y;
		this->effect_id = effect_id;
		this->effect_start = GetTickCount64();
		this->isDeleted = FALSE;
	}
	void Render();
	void Update(DWORD dt);

	BOOLEAN IsDeleted() { return isDeleted;  }
};