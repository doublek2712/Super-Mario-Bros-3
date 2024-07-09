#pragma once
#include "Game.h"
#include "BackgroundElement.h"

#define CARD_QUANTITY	3

#define CARD_BLANK		0
#define CARD_MUSHROOM	1
#define CARD_FLOWER		2
#define CARD_START		3

#define WORLD_DEFAULT	1
#define LIFE_DEFAULT	4
#define SCORE_DEFAULT	0
#define COIN_DEFAULT	0
#define TIMER_DEFAULT	0

#define PANEL_HEIGHT_BUFFER	4
#define PANEL_HEIGHT	28
#define PANEL_WIDTH		152

#define PANEL_SPACE_BETWEEN	8

#define CARD_HEIGHT	(PANEL_HEIGHT)
#define CARD_WIDTH	24

//HUD - Heads-up display
class CHUD
{
	static CHUD* __instance;

	float x, y;

	CBackgroundElement* background;

	//data
	unsigned int world;
	unsigned int life;
	unsigned int score;
	unsigned int coin;
	unsigned int timer;

	vector<int> cards;

	void UpdateRelativePosition();

public:
	static CHUD* GetInstance();
	CHUD();
	void Update();
	void Render();
	
};