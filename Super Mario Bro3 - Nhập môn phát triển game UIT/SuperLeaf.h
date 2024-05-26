#pragma once
#include "GameObject.h"
#include "GlobalState.h"

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16

#define LEAF_LEVEL_LEAF 1
#define LEAF_LEVEL_MUSHROOM 0



class CSuperLeaf : public CGameObject {
	int level;
	int dir;
public:
	CSuperLeaf(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);
	int IsBlocking() { return 0; }
};
