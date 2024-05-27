#pragma once
#include "GameObject.h"

#define PIPE_DIRECTION_HORIZONTAL 2
#define PIPE_DIRECTION_VERTICAL 1



class CPipe : public CGameObject
{
	int dir; // direction, 1 - hori , 2 - verti
	int flip;
	int length;

public:
	CPipe(float x, float y, int dir, int flip, int length) : CGameObject(x, y) {
		this->dir = dir;
		this->length = length;
		this->flip = flip;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};