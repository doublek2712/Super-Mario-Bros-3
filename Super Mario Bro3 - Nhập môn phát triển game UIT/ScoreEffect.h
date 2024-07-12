#pragma once
#include "Effect.h"

#define SCORE_EFFECT_TIME	1000


class CScoreEffect : public CEffect
{
	int score;
public:
	CScoreEffect(float x, float y, int score) : CEffect(x, y) {
		this->score = score;
	}
	void Render() {

	}
	void Update(DWORD dt) {

	}
};