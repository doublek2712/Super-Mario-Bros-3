#include "BackgroundElement.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Animations.h"

#include "Configs.h"



void CBackgroundElement::Render()
{
	if (this->row <= 0 || this->col <=0) return;
	float xx = x ;
	float yy = y ;

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			if (type == BG_ELEMENT_TYPE_SPRITE)
				sprites->Get(this->sprite_id)->Draw(xx, yy);
			else
				animations->Get(this->animation_id)->Render(xx, yy);
			xx += GRID_SIZE;
		}
		yy += GRID_SIZE;
		xx = x ;
	}
}