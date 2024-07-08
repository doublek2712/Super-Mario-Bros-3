#pragma once
#include "GameObject.h"

#define PIPE_DIRECTION_HORIZONTAL 2
#define PIPE_DIRECTION_VERTICAL 1

#define GATE_TYPE_NONE	0
#define GATE_TYPE_ENTRANCE	1
#define GATE_TYPE_EXIT	2

#define MAP_MAIN		-1

class CPipe : public CGameObject
{
	int dir; // direction, 1 - hori , 2 - verti
	int length;
	int map;
	int index;
	int gateType;

	void RenderPipeMain();
	void RenderPipeHidden();
public:
	CPipe(float x, float y, int dir,int length, int map, int gateType, int index = -1) : CGameObject(x, y) {
		this->dir = dir;
		this->length = length;
		this->map = map;
		this->gateType = gateType;
		this->index = index;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	int GetMap() { return map; }
	int GetType() { return gateType;  }
	int GetIndex() { return index;  }
	int GetLength() { return length; }
};