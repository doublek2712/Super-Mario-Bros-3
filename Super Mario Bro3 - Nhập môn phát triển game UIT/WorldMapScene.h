#pragma once
#include "Game.h"
#include "Scene.h"

#include "BackgroundElement.h"
#include "MarioOnWorldMap.h"
#include "Portal.h"

#define EXPLORE_DIRECTION_LEFT		1
#define EXPLORE_DIRECTION_RIGHT		2
#define EXPLORE_DIRECTION_UP		3
#define EXPLORE_DIRECTION_DOWN		4

#define PATH_TYPE_BLANK	0
#define PATH_TYPE_PATH	1
#define PATH_TYPE_STOP	2

#define PORTAL_MAP_BLANK	0
#define	PORTAL_MAP_START	-1

#define WORLD_MAP_STATE_IDLE			100
#define WORLD_MAP_STATE_ENTERING_PORTAL	200
#define WORLD_MAP_STATE_RESTART			300

class CWorldMapScene : public CScene
{
	CMarioOnWorldMap* player;

	vector<LPBGELEMENT> background;

	//map
	int origin_x, origin_y;
	int row, col;
	vector<vector<int>> path;
	vector<vector<int>> portalMap;

	int state;

	unordered_map<int,CPortal*> portals;

	void _ParseSection_BACKGROUND(string line);
	void _ParseSection_MAP_SETTINGS(string line);
	void _ParseSection_PATH(string line);
	void _ParseSection_PLAYER(string line); 
	void _ParseSection_PORTAL(string line);
public:
	CWorldMapScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void SetState(int state);

	CMarioOnWorldMap* GetPlayer() { return player; }

	void ExploreNextMove(float& x, float& y, int direction);
	int GetPortalIfStandingOn(float x, float y);
};