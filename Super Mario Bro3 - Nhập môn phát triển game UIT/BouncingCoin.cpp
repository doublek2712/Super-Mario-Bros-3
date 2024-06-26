#include "BouncingCoin.h"

void CBouncingCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y > def_y && vy != 0) {
		y = def_y;
		vy = 0;
		isDeleted = true;
		return;
	}
	if (y < def_y) {
		vy += BOUNCING_COIN_BOUNCE_RECURE * dt;
	}
}
void CBouncingCoin::SetState(int state) {
	if (this->state == CONTAINED_STATE_ACTIVE) return;
	switch (state) {
	case CONTAINED_STATE_ACTIVE:
		vy = -BOUNCING_COIN_BOUNCE_FORCE;

		break;
	}

	CGameObject::SetState(state);

}

void CBouncingCoin::Render() {
	if (state == CONTAINED_STATE_DEACTIVE) return;
	CCoin::Render();
}