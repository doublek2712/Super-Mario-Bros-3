#include "SuperLeaf.h"
#include "Sprites.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "Mario.h"

CSuperLeaf::CSuperLeaf(float x, float y) :CGameObject(x, y) {
	this->state = CONTAINED_STATE_DEACTIVE;
	this->level = LEAF_LEVEL_LEAF;
	this->dir = 1;
}

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (this->state == CONTAINED_STATE_ACTIVE) {
		y += vy * dt;
		x += vx * dt;
		if(vy <= 0)
			vy += 0.0008f * dt;

		if (vy > 0){
			if (dir == -1) {
				if (vx >= -0.05f)
					vx -= 0.0001f * dt;
				else
				{
					dir = 1;
					//vx = 0;
				}
			}
			else 
			if (dir == 1) {
				if (vx <= 0.05f)
					vx += 0.0001f * dt;
				else
				{
					dir = -1;
					//vx = 0;
				}
			}
		}
	}
}
void CSuperLeaf::Render() {
	if (state == CONTAINED_STATE_DEACTIVE) return;

	CSprites* s = CSprites::GetInstance();
	switch (level)
	{
	case LEAF_LEVEL_MUSHROOM:
		s->Get(ID_SPRITE_POWERUP_MUSHROOM)->Draw(x, y);
		break;
	case LEAF_LEVEL_LEAF:
		if(dir == 1)
			s->Get(ID_SPRITE_POWERUP_LEAF_RIGHT)->Draw(x, y);
		else
			s->Get(ID_SPRITE_POWERUP_LEAF_LEFT)->Draw(x, y);
		break;
	}

}
void CSuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CSuperLeaf::SetState(int state) {
	if (this->state == CONTAINED_STATE_ACTIVE) return;
	switch (state) {
	case CONTAINED_STATE_ACTIVE:
	{
		vy = -0.2f;
		CPlayScene* s = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CMario* player = (CMario*)s->GetPlayer();
		switch (player->GetLevel())
		{
		case MARIO_LEVEL_SMALL:
			break;
		}
		break;
	}
	}
	CGameObject::SetState(state);
}