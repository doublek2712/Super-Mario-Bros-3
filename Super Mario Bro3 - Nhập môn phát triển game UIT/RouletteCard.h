#pragma once
#include "GameObject.h"
#include "Data.h"

#define ROULETTE_CARD_BBOX_WIDTH	16
#define ROULETTE_CARD_BBOX_HEIGHT	16

#define ROULETTE_SPEED	0.2f

#define ROULETTE_TIME	200

#define	ROULETTE_CARD_STATE_IDLE			100
#define	ROULETTE_CARD_STATE_WAS_COLLECTED	200

class CRouletteCard : public CGameObject
{
	int card;

	ULONGLONG roulette_start;
public:
	CRouletteCard(float x, float y) : CGameObject(x, y){
		this->card = CARD_MUSHROOM;
		this->roulette_start = 0;
		this->vx = 0;
		this->vy = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	int IsBlocking() { return 0; }

	int GetCard() { return card;  }
};