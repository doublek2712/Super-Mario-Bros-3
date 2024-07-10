#pragma once

#include "GameObject.h"
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
	CPortal(float x, float y, int index, int scene_id);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void Render();
	int GetSceneId() { return scene_id; }
	int IsBlocking() { return 0; }
};