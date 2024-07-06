#pragma once
#include "GameObject.h"


#define PBUTTON_BBOX_WIDTH 16
#define PBUTTON_BBOX_HEIGHT 16
#define PBUTTON_PRESSED_BBOX_HEIGHT 8

#define PBUTTON_STATE_HIDING	-100
#define PBUTTON_STATE_IDLE		100
#define PBUTTON_STATE_PRESSED	200

#define ID_ANI_PBUTTON_IDLE		12001
#define ID_ANI_PBUTTON_PRESSED	12002

class CPButton : public CGameObject
{
	BOOLEAN isPressed;
	BOOLEAN areBricksHandled;
	BOOLEAN isHiding;
public:
	CPButton(int x, int y): CGameObject(x, y){
		isPressed = FALSE;
		isHiding = FALSE;
		areBricksHandled = FALSE;
		SetState(PBUTTON_STATE_HIDING);
	}
	int IsBlocking() { return !isHiding; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
