#pragma once
#include "Game.h"
#include "Data.h"
#include "BackgroundElement.h"

#define PANEL_WIDTH_BUFFER	8
#define PANEL_HEIGHT_BUFFER	4
#define PANEL_HEIGHT	28
#define PANEL_WIDTH		152

#define PANEL_SPACE_BETWEEN	8

#define CARD_HEIGHT	(PANEL_HEIGHT)
#define CARD_WIDTH	24

#define WORLD_INDEX_BUFFER_WIDTH	37
#define WORLD_INDEX_BUFFER_HEIGHT	7
#define CHARACTER_SIZE	8

#define LIFE_MAX_DIGIT		2
#define LIFE_BUFFER_WIDTH	29
#define LIFE_BUFFER_HEIGHT	15

#define SCORE_MAX_DIGIT	7
#define SCORE_BUFFER_WIDTH	52
#define SCORE_BUFFER_HEIGHT	15

#define COIN_MAX_DIGIT	2
#define COIN_BUFFER_WIDTH	132
#define COIN_BUFFER_HEIGHT	7

#define TIMER_MAX_DIGIT	3
#define TIMER_BUFFER_WIDTH	124
#define TIMER_BUFFER_HEIGHT	15

#define TRIANGLE_MAX_QUANTITY	6
#define TRIANGLE_BUFFER_WIDTH	52
#define TRIANGLE_BUFFER_HEIGHT	7

#define P_BAGDE_BUFFER_WIDTH	101
#define P_BAGDE_BUFFER_HEIGHT	7

#define P_BAGDE_WIDTH	16
#define P_BAGDE_HEIGHT	8

#define ID_ANI_P_BAGDE_FLICKER	14000

//HUD - Heads-up display
class CHUD
{
	static CHUD* __instance;

	float x, y;

	CBackgroundElement* background;

	void UpdateRelativePosition();

public:
	static CHUD* GetInstance();
	CHUD();
	void Update();
	void Render();
	
};