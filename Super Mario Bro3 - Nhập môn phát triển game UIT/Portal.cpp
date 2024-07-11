#include "Portal.h"
#include "Sprites.h"
#include "debug.h"
#include "AssetIDs.h"

CPortal::CPortal(float x, float y, int index, int scene_id) : CGameObject(x, y)
{
	this->index = index;
	this->scene_id = scene_id;
	SetState(PORTAL_STATE_OPEN);
}
void CPortal::Render()
{
	int spriteId = -1;
	if (state == PORTAL_STATE_OPEN)
		spriteId = ID_SPRITE_PORTAL_NUMBER - index;
	else
		spriteId = ID_SPRITE_PORTAL_PASS;

	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
		
}

