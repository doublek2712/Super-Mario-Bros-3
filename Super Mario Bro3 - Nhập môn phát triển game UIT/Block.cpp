#include "Block.h"
#include "Configs.h"
#include "debug.h"

void CBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	y += vy * dt;
	if (y > def_y) {
		y = def_y;
		vy = 0;
		this->SetState(BLOCK_STATE_EMPTY);
	}
	if (y < def_y) {
		vy += BLOCK_BOUNCE_RECURE * dt;
	}

	DebugOutTitle(L"Block[x=%f,y=%f]", x, y);
}
void CBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == BLOCK_STATE_EMPTY)
		aniId = ID_ANI_EMPTY_BLOCK;
	else if (state == BLOCK_STATE_COLLIDED || state == BLOCK_STATE_IDLE)
		aniId = ID_ANI_Q_BLOCK;

	animations->Get(aniId)->Render(x,y);

	RenderBoundingBox();
}

void CBlock::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BLOCK_BBOX_WIDTH /2;
	t = y - BLOCK_BBOX_HEIGHT /2;
	r = l + BLOCK_BBOX_WIDTH;
	b = t + BLOCK_BBOX_HEIGHT;
}

void CBlock::SetState(int state) {
	if (this->state == BLOCK_STATE_EMPTY) return;
	switch (state) {
	case BLOCK_STATE_COLLIDED:
		vy = -BLOCK_BOUNCE_FORCE;
		break;
	case BLOCK_STATE_EMPTY:
		break;
	}

	CGameObject::SetState(state);

}