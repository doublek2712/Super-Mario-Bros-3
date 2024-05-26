#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"

#include "Configs.h"

void CPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x  - GRID_SIZE / 2 + rect.right / 2;
	float yy = y ;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
void CPlatform::Render()
{
	if (this->length <= 0) return; 
	float xx = x ; 
	float yy = y ;
	CSprites * s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(xx, yy);
	xx += GRID_SIZE;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(xx, yy);
		xx += GRID_SIZE;
	}
	if (length>1)
		s->Get(this->spriteIdEnd)->Draw(xx, yy);

	
	//RenderBoundingBox();
	
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = GRID_SIZE / 2;
	l = x  - cellWidth_div_2;
	t = y  - GRID_SIZE / 2;
	r = l + GRID_SIZE * this->length;
	b = t + GRID_SIZE;
}

int CPlatform::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}
