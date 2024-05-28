#pragma once
#include "Block.h"
#include "AssetIDs.h"


class CWood : public CBlock
{
public:
	CWood(float x, float y) : CBlock(x,y) {
		this->x = x;
		this->y = y;
	}

	int IsBlocking() { return 1; }
	void Render() {
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_WOOD)->Draw(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){}
};