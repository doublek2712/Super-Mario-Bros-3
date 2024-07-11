#include "Data.h"
#include "Mario.h"

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
	current_map = -1; // mean start
}