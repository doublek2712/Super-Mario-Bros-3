#pragma once
#include "Koopa.h"

#define PARAKOOPA_FLY_SPEED		0.16f

#define PARAKOOPA_BBOX_HEIGHT 28

#define ID_ANI_PARAKOOPA_GREEN_WALKING_LEFT		8201
#define ID_ANI_PARAKOOPA_GREEN_WALKING_RIGHT	8202


class CParaKoopa : public CKoopa
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CParaKoopa(float x, float y, BOOLEAN block);
	virtual void SetState(int state);
};