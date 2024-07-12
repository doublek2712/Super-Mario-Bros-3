#include "LifeUpMushroom.h"
#include "AssetIDs.h"
#include "Mario.h"
#include "Configs.h"
#include "ScoreData.h"

#include "debug.h"

CLifeUpMushroom::CLifeUpMushroom(float x, float y) :CSuperMushroom(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->def_y = y - GRID_SIZE;
	SetState(CONTAINED_STATE_DEACTIVE);
}
void CLifeUpMushroom::Render()
{
	if (state == CONTAINED_STATE_DEACTIVE || state == CONTAINED_STATE_ACTIVE) return;
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_LIFEUP_MUSHROOM)->Draw(x, y);

	//RenderBoundingBox();
}