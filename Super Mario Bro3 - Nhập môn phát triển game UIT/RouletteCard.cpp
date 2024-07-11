#include "RouletteCard.h"
#include "AssetIDs.h"
void CRouletteCard::Render() {
	CSprites::GetInstance()->Get(ID_SPRITE_ROULETTE_CARD - card - 1)->Draw(x, y);
}
void CRouletteCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (GetTickCount64() - roulette_start > ROULETTE_TIME)
	{
		card = (card + 1) % CARD_QUANTITY;
		roulette_start = GetTickCount64();
	}

	x += vx * dt;
	y += vy * dt;
}
void CRouletteCard::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - ROULETTE_CARD_BBOX_WIDTH / 2;
	t = y - ROULETTE_CARD_BBOX_HEIGHT / 2;
	r = l + ROULETTE_CARD_BBOX_WIDTH;
	b = t + ROULETTE_CARD_BBOX_HEIGHT;
}
void CRouletteCard::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case ROULETTE_CARD_STATE_WAS_COLLECTED:
		vy = -ROULETTE_SPEED;
		break;
	}
}