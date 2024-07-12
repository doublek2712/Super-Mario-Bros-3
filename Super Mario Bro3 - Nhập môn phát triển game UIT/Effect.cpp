#include "Effect.h"
#include "Animations.h"

void CEffect::Render() {
	if (isDeleted) return;
	CAnimations* animations = CAnimations::GetInstance();
	if (effect_id == EFFECT_ID_SCORE_100)
		animations->Get(ID_ANI_SCORE_100)->Render(x, y);
	if (effect_id == EFFECT_ID_SCORE_1000)
		animations->Get(ID_ANI_SCORE_1000)->Render(x, y);

}
void CEffect::Update(DWORD dt) {
	if (isDeleted) return;
	y += -EFFECT_SCORE_SPEED * dt;
	if (GetTickCount64() - effect_start > EFFECT_SCORE_TIME)
	{
		isDeleted = TRUE;
	}
}