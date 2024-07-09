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
	world = WORLD_DEFAULT;
	life = LIFE_DEFAULT;
	score = SCORE_DEFAULT;
	coin = COIN_DEFAULT;
	timer = TIMER_DEFAULT;

	for (int i = 0; i < CARD_QUANTITY; i++)
		cards.push_back(CARD_BLANK);

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

	//render bg
	background->Render();

	//render panel
	sprires->Get(ID_SPRITE_HUD_PANEL)->Draw(
		x+PANEL_WIDTH/2, 
		y + (PANEL_HEIGHT/2 - GRID_SIZE/2) + PANEL_HEIGHT_BUFFER);

	//render cards
	float card_star_x = x + PANEL_WIDTH + PANEL_SPACE_BETWEEN + CARD_WIDTH/2;

	for (int i = 0; i < cards.size(); i++)
		sprires->Get(ID_SPRITE_CARD + cards[i])->Draw(
			card_star_x + CARD_WIDTH * i,
			y + (CARD_HEIGHT / 2 - GRID_SIZE / 2) + PANEL_HEIGHT_BUFFER
		);
}