#pragma once

#include "Platform.h"

class CGround : public CPlatform
{

public:
	CGround(float x, float y,
		int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end)
		:CPlatform(x, y, length, sprite_id_begin, sprite_id_middle, sprite_id_end){}

	void Update(DWORD dt) {}
	int IsDirectionColliable(float nx, float ny) { return 1; }
};

typedef CGround* LPGROUND;