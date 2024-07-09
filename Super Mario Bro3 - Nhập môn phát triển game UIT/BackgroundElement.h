#pragma once
#include "Game.h"
#include "Utils.h"
#include "debug.h"

#define BG_ELEMENT_TYPE_SPRITE		1
#define BG_ELEMENT_TYPE_ANIMATION	2

class CBackgroundElement {
	float x, y;
	int row, col;
	int sprite_id;
	int animation_id;
	int type;
public:

	//constructor with sprite element and x, y on grid input
	CBackgroundElement(
		int x,
		int y,
		int row,
		int col,
		int id,
		int type = BG_ELEMENT_TYPE_SPRITE
	) {
		this->x = x;
		this->y = y;
		gridToreal(this->x, this->y);
		this->row = row;
		this->col = col;
		this->type = type;
		if (type == BG_ELEMENT_TYPE_SPRITE)
			this->sprite_id = id;
		else
			this->animation_id = id;
	}

	//constructor with sprite element and x, y on real input
	CBackgroundElement(
		float x,
		float y,
		int row,
		int col,
		int id,
		int type = BG_ELEMENT_TYPE_SPRITE
		) {
		this->x = x;
		this->y = y;
		this->row = row;
		this->col = col;
		this->type = type;
		if (type == BG_ELEMENT_TYPE_SPRITE)
			this->sprite_id = id;
		else
			this->animation_id = id;
	}


	void Render();
	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
};

typedef CBackgroundElement* LPBGELEMENT;