#include "Data.h"
#include "Mario.h"
#include "WorldMapScene.h"

void CData::ResetData() {
	world = WORLD_DEFAULT;
	life = LIFE_DEFAULT;
	score = SCORE_DEFAULT;
	coin = COIN_DEFAULT;
	timer = TIMER_DEFAULT;
	speed = 0;

	for (int i = 0; i < CARD_QUANTITY; i++)
		cards.push_back(CARD_BLANK);

	player_level = MARIO_LEVEL_SMALL;
	current_map = PORTAL_MAP_START; // mean start
	passed_map = PORTAL_MAP_START;
}