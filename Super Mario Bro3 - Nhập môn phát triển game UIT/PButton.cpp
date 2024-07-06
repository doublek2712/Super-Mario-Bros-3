#include "PButton.h"
#include "Brick.h"

void CPButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	int height = (state == PBUTTON_STATE_IDLE) ? PBUTTON_BBOX_HEIGHT : PBUTTON_PRESSED_BBOX_HEIGHT;
	l = x - PBUTTON_BBOX_WIDTH / 2;
	t = y - height / 2;
	r = l + PBUTTON_BBOX_WIDTH;
	b = t + height;
}
void CPButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (areBricksHandled)
		return;
	if (isPressed)
	{
		for (int i = 0; i < coObjects->size(); i++)
			if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
				if(brick->GetState() != BRICK_STATE_EMPTY)
					brick->SetState(BRICK_STATE_TRANS_TO_COIN);
			}
		areBricksHandled = TRUE;
	}
}
void CPButton::Render() {
	if (isHiding)
		return;

	int aniId = -1;
	if (state == PBUTTON_STATE_IDLE)
		aniId = ID_ANI_PBUTTON_IDLE;
	else
		aniId = ID_ANI_PBUTTON_PRESSED;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
void CPButton::SetState(int state) {
	switch (state)
	{
	case PBUTTON_STATE_HIDING:
		isHiding = TRUE;
		break;
	case PBUTTON_STATE_IDLE:
		isHiding = FALSE;
		break;
	case PBUTTON_STATE_PRESSED:
		y += (PBUTTON_BBOX_HEIGHT - PBUTTON_PRESSED_BBOX_HEIGHT) / 2;
		isPressed = TRUE;
		break;
	}
	CGameObject::SetState(state);
}
