#include "BackgroundElement.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Configs.h"

void CBackgroundElement::Render()
{
	if (this->row <= 0 || this->col <=0) return;
	float xx = x * GRID_SIZE + WD_WIDTH_BUFFER;
	float yy = y * GRID_SIZE + WD_HEIGHT_BUFFER;
	CSprites* s = CSprites::GetInstance();
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			s->Get(this->sprite_id)->Draw(xx, yy);
			xx += GRID_SIZE;
		}
		yy += GRID_SIZE;
		xx = x * GRID_SIZE + WD_WIDTH_BUFFER;
	}
}