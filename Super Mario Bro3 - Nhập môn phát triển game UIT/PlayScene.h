#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Block.h"
#include "Mario.h"
#include "Goomba.h"
#include "BackgroundElement.h"


#define PLAY_STATE_PLAYING 0
#define PLAY_STATE_LOSE 1
#define PLAY_STATE_WIN	2

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;
	vector<LPBGELEMENT> background;
	int b_left, b_right, b_top, b_bottom;


	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_BACKGROUND(string line);
	void _ParseSection_BOUNDARIES(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

