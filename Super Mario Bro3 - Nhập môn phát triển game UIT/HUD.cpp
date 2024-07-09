#include "HUD.h"
#include "Configs.h"
#include "debug.h"

#include "AssetIDs.h"
#include "Sprites.h"

CHUD* CHUD::__instance = NULL;

CHUD* CHUD::GetInstance() {
	if (__instance == NULL) __instance = new CHUD();
	return __instance;
}
CHUD::CHUD() {


	CGame* game = CGame::GetInstance();
	float s_width, s_height;
	float cx, cy;
	game->GetScreenSize(s_width, s_height);
	game->GetCamPos(cx, cy);

	this->x = cx;
	this->y = s_height + cy - GRID_SIZE * 3;

	background = new CBackgroundElement(x, y, 4, s_width/GRID_SIZE + 1, ID_SPRITE_BG_COLOR_BLACK);
}

void CHUD::UpdateRelativePosition() {
	// get cam pos & screen size
	CGame* game = CGame::GetInstance();
	float s_width, s_height;
	float cx, cy;
	game->GetScreenSize(s_width, s_height);
	game->GetCamPos(cx, cy);

	this->x = cx;
	this->y = s_height + cy - GRID_SIZE * 3;

}
void CHUD::Update() {
	UpdateRelativePosition();
	background->SetPosition(x,y);
}
void CHUD::Render() {
	CSprites* sprires = CSprites::GetInstance();
	CData* data = CGame::GetInstance()->GetData();

	//render bg
	background->Render();

	//render panel
	sprires->Get(ID_SPRITE_HUD_PANEL)->Draw(
		x + (PANEL_WIDTH/2 - GRID_SIZE/2) + PANEL_WIDTH_BUFFER,
		y + (PANEL_HEIGHT/2 - GRID_SIZE/2) + PANEL_HEIGHT_BUFFER);

	//render cards
	float card_star_x = x + (PANEL_WIDTH - GRID_SIZE / 2) + PANEL_WIDTH_BUFFER + PANEL_SPACE_BETWEEN + CARD_WIDTH/2;

	for (int i = 0; i < data->GetCards().size(); i++)
		sprires->Get(ID_SPRITE_CARD + data->GetCards()[i])->Draw(
			card_star_x + CARD_WIDTH * i,
			y + (CARD_HEIGHT / 2 - GRID_SIZE / 2) + PANEL_HEIGHT_BUFFER
		);

	//render character
	// 
	// world
	sprires->Get(ID_SPRITE_NUMBER + data->GetWorld())->Draw(
		x + PANEL_WIDTH_BUFFER + WORLD_INDEX_BUFFER_WIDTH - GRID_SIZE/2 + CHARACTER_SIZE /2,
		y + PANEL_HEIGHT_BUFFER + WORLD_INDEX_BUFFER_HEIGHT - GRID_SIZE/2 + CHARACTER_SIZE / 2
	);
	// life
	{
		UINT life = data->GetLife();
		int count = 0;
		while (life > 0)
		{
			int digit = life % 10;
			sprires->Get(ID_SPRITE_NUMBER + digit)->Draw(
				x + PANEL_WIDTH_BUFFER + LIFE_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (LIFE_MAX_DIGIT - count - 1),
				y + PANEL_HEIGHT_BUFFER + LIFE_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
			count++;
			life /= 10;
		}
	}
	//score
	{
		UINT score = data->GetScore();
		int count = 0;
		while (score > 0)
		{
			int digit = score % 10;
			sprires->Get(ID_SPRITE_NUMBER + digit)->Draw(
				x + PANEL_WIDTH_BUFFER + SCORE_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (SCORE_MAX_DIGIT - (count + 1)),
				y + PANEL_HEIGHT_BUFFER + SCORE_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
			count++;
			score /= 10;
		}
		while (count < SCORE_MAX_DIGIT)
		{
			sprires->Get(ID_SPRITE_NUMBER + 0)->Draw(
				x + PANEL_WIDTH_BUFFER + SCORE_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (SCORE_MAX_DIGIT - (count + 1)),
				y + PANEL_HEIGHT_BUFFER + SCORE_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
			count++;
		}
	}
	//coin
	{
		UINT coin = data->GetCoin();
		int count = 0;
		while (coin > 0)
		{
			int digit = coin % 10;
			sprires->Get(ID_SPRITE_NUMBER + digit)->Draw(
				x + PANEL_WIDTH_BUFFER + COIN_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (COIN_MAX_DIGIT - (count + 1)),
				y + PANEL_HEIGHT_BUFFER + COIN_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
			count++;
			coin /= 10;
		}

		if (count == 0) {
			sprires->Get(ID_SPRITE_NUMBER + 0)->Draw(
				x + PANEL_WIDTH_BUFFER + COIN_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (COIN_MAX_DIGIT - 1),
				y + PANEL_HEIGHT_BUFFER + COIN_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
		}
	}
	//timer
	{
		UINT timer = data->GetTimer();
		int count = 0;
		while (timer > 0)
		{
			int digit = timer % 10;
			sprires->Get(ID_SPRITE_NUMBER + digit)->Draw(
				x + PANEL_WIDTH_BUFFER + TIMER_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (TIMER_MAX_DIGIT - (count + 1)),
				y + PANEL_HEIGHT_BUFFER + TIMER_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
			count++;
			timer /= 10;
		}
		while (count < TIMER_MAX_DIGIT)
		{
			sprires->Get(ID_SPRITE_NUMBER + 0)->Draw(
				x + PANEL_WIDTH_BUFFER + TIMER_BUFFER_WIDTH - GRID_SIZE / 2 + CHARACTER_SIZE / 2 + CHARACTER_SIZE * (TIMER_MAX_DIGIT - (count + 1)),
				y + PANEL_HEIGHT_BUFFER + TIMER_BUFFER_HEIGHT - GRID_SIZE / 2 + CHARACTER_SIZE / 2
			);
			count++;
		}
	}


}