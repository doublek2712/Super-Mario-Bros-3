#include "Pipe.h"
#include "AssetIDs.h"
#include "Configs.h"

void CPipe::Render() {

	CSprites* s = CSprites::GetInstance();
	//draw body of pipe
	for (int i = 0; i < length; i++) {
		if (dir == PIPE_DIRECTION_HORIZONTAL) {
			s->Get(ID_SPRITE_PIPE_BODY_LEFT)->Draw(x, y - GRID_SIZE * i);
			s->Get(ID_SPRITE_PIPE_BODY_RIGHT)->Draw(x, y - GRID_SIZE * i);
		}
		else 
		if (dir == PIPE_DIRECTION_VERTICAL) {
			s->Get(ID_SPRITE_PIPE_BODY_LEFT)->Draw(x, y - GRID_SIZE * i);
			s->Get(ID_SPRITE_PIPE_BODY_RIGHT)->Draw(x + GRID_SIZE, y - GRID_SIZE * i);
		}
	}
	s->Get(ID_SPRITE_PIPE_HEAD_LEFT)->Draw(x, y - GRID_SIZE * length);
	s->Get(ID_SPRITE_PIPE_HEAD_RIGHT)->Draw(x + GRID_SIZE, y - GRID_SIZE * length);

	//RenderBoundingBox();
	
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - GRID_SIZE / 2;
	t = y - GRID_SIZE / 2 - GRID_SIZE * (length );
	r = l + 2 * GRID_SIZE;
	b = y + GRID_SIZE / 2;
}