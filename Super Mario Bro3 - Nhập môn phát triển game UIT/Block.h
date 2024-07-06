#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Configs.h"
#include "debug.h"

#include "BouncingCoin.h"

#define ID_ANI_Q_BLOCK 10000
#define ID_ANI_EMPTY_BLOCK 10001

#define BLOCK_STATE_IDLE 100
#define BLOCK_STATE_COLLIDED_BELOW 200
#define BLOCK_STATE_COLLIDED_SIDE 300
#define BLOCK_STATE_EMPTY 400

#define BRICK_WIDTH 16
#define BLOCK_BBOX_WIDTH 16
#define BLOCK_BBOX_HEIGHT 16

#define BLOCK_BOUNCE_FORCE 0.3f
#define BLOCK_BOUNCE_RECURE 0.008f

#define CONTAIN_COIN 0
#define CONTAIN_1UP_MUSHROOM 1
#define CONTAIN_SUPER_LEAF 2


class CBlock : public CGameObject {
	float def_x, def_y;
	int contain_type;
	CGameObject* item;
public:
	CBlock(float x, float y,int contain_type, CGameObject* item) : CGameObject(x,y) {
		this->state = BLOCK_STATE_IDLE;
		def_x = x;
		def_y = y;
		this->contain_type = contain_type;
		this->item = item;
	}
	CBlock(float x, float y) : CGameObject(x, y){
		this->item = nullptr;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);
};