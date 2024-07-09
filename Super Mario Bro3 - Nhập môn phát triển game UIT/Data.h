#pragma once


#define WORLD_DEFAULT	1
#define LIFE_DEFAULT	4
#define SCORE_DEFAULT	0
#define COIN_DEFAULT	0
#define TIMER_DEFAULT	0

#define CARD_QUANTITY	3

#define CARD_BLANK		0
#define CARD_MUSHROOM	1
#define CARD_FLOWER		2
#define CARD_START		3

// this class contain all data game
class CData
{
	UINT world;
	UINT life;
	UINT score;
	UINT coin;
	UINT timer;
	vector<int> cards;

public:
	CData() {
		world = WORLD_DEFAULT;
		life = LIFE_DEFAULT;
		score = SCORE_DEFAULT;
		coin = COIN_DEFAULT;
		timer = TIMER_DEFAULT;

		for (int i = 0; i < CARD_QUANTITY; i++)
			cards.push_back(CARD_BLANK);
	}

	//getter
	UINT GetWorld() { return world; }
	UINT GetLife() { return life; }
	UINT GetScore() { return score; }
	UINT GetCoin() { return coin; }
	UINT GetTimer() { return timer; }
	vector<int> GetCards() { return cards; }

	//setter
	void SetWorld(UINT world) { this->world = world; }
	void SetLife(UINT life) { this->life = life; }
	void SetScore(UINT score) { this->score = score; }
	void SetCoin(UINT coin) { this->coin = coin; }
	void SetTimer(UINT timer) { this->timer = timer; }

};

typedef CData* LPDATA;