#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

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
	int passed_map;

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
	int GetPassedMap() { return passed_map;  }

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
		for(int i=0; i<cards.size();i++)
			if (cards[i] == CARD_BLANK)
			{
				cards[i] = card;
				break;
			}
	}
	void PassCurrentMap() {
		passed_map = current_map;
	}

	//reset
	void ResetData();

};

typedef CData* LPDATA;