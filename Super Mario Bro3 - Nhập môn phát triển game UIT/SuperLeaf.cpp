#include "SuperLeaf.h"
#include "Sprites.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "Mario.h"

CSuperLeaf::CSuperLeaf(float x, float y, CSuperMushroom* mushroom) :CGameObject(x, y) {
	this->state = CONTAINED_STATE_DEACTIVE;
	this->dir = 1;
	this->mushroom = mushroom;
}

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (this->state == CONTAINED_STATE_ACTIVE) {
		y += vy * dt;
		x += vx * dt;
		if(vy <= 0)
			vy += 0.0008f * dt;

		if (vy > 0){
			vy = 0.0008f * dt;
			if (dir == -1) {
				if (vx >= -0.05f)
					vx -= 0.0001f * dt;
				else
				{
					dir = 1;
				}
			}
			else 
			if (dir == 1) {
				if (vx <= 0.05f)
					vx += 0.0001f * dt;
				else
				{
					dir = -1;
				}
			}
		}
	}

	if (state == LEAF_STATE_DIE)
		isDeleted = true;
}
void CSuperLeaf::Render() {
	if (state == CONTAINED_STATE_DEACTIVE || state == LEAF_STATE_DIE) return;

	CSprites* s = CSprites::GetInstance();

		if(dir == 1)
			s->Get(ID_SPRITE_POWERUP_LEAF_RIGHT)->Draw(x, y);
		else
			s->Get(ID_SPRITE_POWERUP_LEAF_LEFT)->Draw(x, y);
		//RenderBoundingBox();

}
void CSuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CSuperLeaf::SetState(int state) {
	//if (this->state == CONTAINED_STATE_ACTIVE) return;
	switch (state) {
	case CONTAINED_STATE_ACTIVE:
	{
		CPlayScene* s = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CMario* player = (CMario*)s->GetPlayer();
		switch (player->GetLevel())
		{
		case MARIO_LEVEL_SMALL:
			mushroom->SetState(state);
			SetState(LEAF_STATE_DIE);
			return;
		default:
			vy = -0.2f;
			break;
		}
		break;
	}

	}
	CGameObject::SetState(state);
}
int CSuperLeaf::IsCollidable() {
	return (state != CONTAINED_STATE_DEACTIVE);
}