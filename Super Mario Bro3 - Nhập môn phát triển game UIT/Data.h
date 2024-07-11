#pragma once
#include "Mario.h"

#define WORLD_DEFAULT	1
#define LIFE_DEFAULT	4
#define SCORE_DEFAULT	0
#define COIN_DEFAULT	0
#define TIMER_DEFAULT	0
#define TIMER_PLAYSCENE	300

#define CARD_QUANTITY	3

#define CARD_BLANK		0
#define CARD_MUSHROOM	1
#define CARD_FLOWER		2
#define CARD_START		3

// this class contain all data game
class CData
{
	// HUD data
	UINT world;
	UINT life;
	UINT score;
	UINT coin;
	UINT timer;
	float speed;
	vector<int> cards;

	// general data
	int player_level;
	int current_map;

public:
	CData() {
		ResetData();
	}

	//getter
	UINT GetWorld() { return world; }
	UINT GetLife() { return life; }
	UINT GetScore() { return score; }
	UINT GetCoin() { return coin; }
	UINT GetTimer() { return timer; }
	float GetSpeed() { return speed; }
	vector<int> GetCards() { return cards; }

	int GetPlayerLevel() { return player_level; }
	int GetCurrentMap() { return current_map; }

	//setter
	void SetWorld(UINT world) { this->world = world; }
	void SetLife(UINT life) { this->life = life; }
	void SetScore(UINT score) { this->score = score; }
	void SetCoin(UINT coin) { this->coin = coin; }
	void SetTimer(UINT timer) { this->timer = timer; }
	void SetSpeed(float speed) { this->speed = speed; }

	void SetPlayerLevel(int player_level) { this->player_level = player_level; }
	void SetCurrentMap(int current_map) { this->current_map = current_map; }

	//add
	void AddCoin(int coin) { this->coin += coin; }
	void AddLife(int life) { this->life += life; }
	void AddScore(int score) { this->score += score; }
	void AddTimer(int time) { this->timer += time; }
	void AddCard(int card)
	{
		for(auto i : cards)
			if (i == CARD_BLANK)
			{
				i = card;
				break;
			}
	}

	//reset
	void ResetData() {
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

};

typedef CData* LPDATA;