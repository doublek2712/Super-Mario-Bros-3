#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Block.h"
#include "Mario.h"
#include "Goomba.h"
#include "BackgroundElement.h"
#include "Pipe.h"
#include "Effect.h"

#define PLAY_STATE_START 0
#define PLAY_STATE_PLAYING 1
#define PLAY_STATE_PAUSE -1
#define PLAY_STATE_LOSE 2
#define PLAY_STATE_WIN	3
#define PLAY_STATE_TIMEOUT	4

#define DELAY_TIME_LOSE	2000
#define DELAY_TIME_WIN	2000

struct Boundary {
	int left;
	int top;
	int right;
	int bottom;
};

struct PipePair {
	CPipe* entrance;
	CPipe* exit;
};

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	// A roulette card - Condition to win
	LPGAMEOBJECT card; 

	vector<LPGAMEOBJECT> objects;
	vector<LPBGELEMENT> background;
	vector<PipePair> pipes;
	vector<CEffect*> effects;

	Boundary currentBoundary;

	Boundary mainBoundary;
	vector<Boundary> hiddenMapBoundary;

	BOOLEAN isCamYPosAdjust;

	int state;

	//timer 
	ULONGLONG second_count_start;
	ULONGLONG lose_start;
	ULONGLONG win_start;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_BACKGROUND(string line);
	void _ParseSection_BOUNDARIES(string line);
	void _ParseSection_HIDDENMAPS(string line);

	void LoadAssets(LPCWSTR assetFile);

	void AdjustCamPos();

	

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void Pause();
	void UnPause();

	void SetState(int state);
	int GetState() {
		return state;
	};

	LPGAMEOBJECT GetPlayer() { return player; }

	void SpawnObject(LPGAMEOBJECT obj);
	void SpawnEffect(CEffect* eff);

	BOOLEAN IsFallOff(float obj_y) {
		return (obj_y >= currentBoundary.bottom * GRID_SIZE);
	}

	CPipe* GetExitPipeWithIndex(int index) { 
		if(index+1 <= pipes.size())
			return pipes[index].exit; 
		return nullptr;
	}

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

