#pragma once
#include "Game.h"
#include "Utils.h"

class CBackgroundElement {
	float x, y;
	int row, col;
	int sprite_id;

public:
	CBackgroundElement(
		int x,
		int y,
		int row,
		int col,
		int sprite_id) {
		this->x = x;
		this->y = y;
		gridToreal(this->x, this->y);
		this->row = row;
		this->col = col;
		this->sprite_id = sprite_id;
	}

	void Render();
};

typedef CBackgroundElement* LPBGELEMENT;