#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "debug.h"
#include "AssetIDs.h"

#define	PORTAL_STATE_OPEN	100
#define	PORTAL_STATE_CLOSE	200



/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	int index;
public:
	CPortal(float x, float y, int index, int scene_id) : CGameObject(x, y)
	{
		this->index = index;
		this->scene_id = scene_id;
		SetState(PORTAL_STATE_OPEN);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void Render() 
	{
		int spriteId = -1;
		if (state == PORTAL_STATE_OPEN)
			spriteId = ID_SPRITE_PORTAL_NUMBER - index;
		else
			spriteId = ID_SPRITE_PORTAL_PASS;

		CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
	}
	int GetSceneId() { return scene_id; }
	int IsBlocking() { return 0; }
};