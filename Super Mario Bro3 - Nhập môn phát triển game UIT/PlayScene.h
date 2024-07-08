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


#define PLAY_STATE_PLAYING 0
#define PLAY_STATE_LOSE 1
#define PLAY_STATE_WIN	2


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

	vector<LPGAMEOBJECT> objects;
	vector<LPBGELEMENT> background;
	vector<PipePair> pipes;

	Boundary currentBoundary;

	Boundary mainBoundary;
	vector<Boundary> hiddenMapBoundary;

	BOOLEAN isCamYPosAdjust;

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

	LPGAMEOBJECT GetPlayer() { return player; }

	void SpawnObject(LPGAMEOBJECT obj);

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

