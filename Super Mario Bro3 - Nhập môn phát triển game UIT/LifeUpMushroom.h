#pragma once
#include "GlobalState.h"
#include "SuperMushroom.h"


class CLifeUpMushroom : public CSuperMushroom
{
public:
	CLifeUpMushroom(float x, float y);
	virtual void Render();
};