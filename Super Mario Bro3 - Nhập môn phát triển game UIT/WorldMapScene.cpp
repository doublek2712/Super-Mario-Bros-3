#include "WorldMapScene.h"
#include "WorldMapKeyHandler.h"

#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Configs.h"
#include "debug.h"
#include "HUD.h"
#include "AssetLoader.h"
#include "Utils.h"
#include "Data.h"


#define WSCENE_SECTION_UNKNOWN -1
#define WSCENE_SECTION_ASSETS	1
#define WSCENE_SECTION_BACKGROUND	2
#define WSCENE_SECTION_PORTALS	3
#define WSCENE_SECTION_PATH	4
#define WSCENE_SECTION_MAP_SETTINGS 5
#define WSCENE_SECTION_PLAYER	6

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

CWorldMapScene::CWorldMapScene(int id, LPCWSTR filePath) :
	CScene(id, filePath) {
	key_handler = new CWorldMapKeyHandler(this);
	row = 0;
	col = 0;
	origin_x = 0;
	origin_y = 0;
	player = NULL;
}

void CWorldMapScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = WSCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = WSCENE_SECTION_ASSETS; continue; };
		if (line == "[BACKGROUND]") { section = WSCENE_SECTION_BACKGROUND; continue; };
		if (line == "[PORTALS]") { section = WSCENE_SECTION_PORTALS; continue; };
		if (line == "[PATH]") { section = WSCENE_SECTION_PATH; continue; };
		if (line == "[MAP_SETTINGS]") { section = WSCENE_SECTION_MAP_SETTINGS; continue; };
		if (line == "[PLAYER]") { section = WSCENE_SECTION_PLAYER; continue; };
		if (line[0] == '[') { section = WSCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case WSCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case WSCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
		case WSCENE_SECTION_PORTALS: _ParseSection_PORTAL(line); break;
		case WSCENE_SECTION_PATH: _ParseSection_PATH(line); break;
		case WSCENE_SECTION_MAP_SETTINGS: _ParseSection_MAP_SETTINGS(line); break;
		case WSCENE_SECTION_PLAYER: _ParseSection_PLAYER(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);

	
	//set state
	SetState(WORLD_MAP_STATE_IDLE);
}
void CWorldMapScene::_ParseSection_BACKGROUND(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	LPBGELEMENT element = nullptr;

	int row = atoi(tokens[2].c_str());
	int col = atoi(tokens[3].c_str());
	int id = atoi(tokens[4].c_str());

	if (tokens.size() > 6) // that mean this one use real position instead of grid
	{
		float x = atoi(tokens[0].c_str());
		float y = atoi(tokens[1].c_str());

		int type = atoi(tokens[5].c_str());
		element = new CBackgroundElement(x, y, row, col, id, type);
	}
	else {
		int x = atoi(tokens[0].c_str());
		int y = atoi(tokens[1].c_str());

		if (tokens.size() == 6)
		{
			int type = atoi(tokens[5].c_str());
			element = new CBackgroundElement(x, y, row, col, id, type);
		}
		else
			element = new CBackgroundElement(x, y, row, col, id);

	}


	this->background.push_back(element);
}
void CWorldMapScene::_ParseSection_PLAYER(string line) {

	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines

	float x = atoi(tokens[0].c_str()) + origin_x;
	float y = atoi(tokens[1].c_str()) + origin_y;

	gridToreal(x, y);

	player = new CMarioOnWorldMap(x, y);

}
void CWorldMapScene::_ParseSection_MAP_SETTINGS(string line) {

	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines

	if (tokens[0] == "ORIGIN")
	{
		origin_x = atoi(tokens[1].c_str());
		origin_y = atoi(tokens[2].c_str());
	}
	else if (tokens[0] == "ROW") {
		row = atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "COL") {
		col = atoi(tokens[1].c_str());
	}

}
void CWorldMapScene::_ParseSection_PATH(string line) {

	vector<string> tokens = split(line);

	if (tokens.size() < col) return; // skip invalid lines

	vector<int> newRow;
	for (int i = 0; i < tokens.size(); i++)
		newRow.push_back(atoi(tokens[i].c_str()));

	path.push_back(newRow);
}
void CWorldMapScene::_ParseSection_PORTAL(string line) {
	vector<string> tokens = split(line);

	//portal - scene_id
	if (tokens.size() < 3) return; // skip invalid lines

	if (tokens[0] == "SCENE_ID")
	{
		int index = atoi(tokens[1].c_str());
		int scene_id = atoi(tokens[2].c_str());

		portals[index] = new CPortal(0, 0, index, scene_id);

		return;
	}

	//portal map
	if (tokens.size() < col) return; // skip invalid lines

	vector<int> newRow;
	for (int i = 0; i < tokens.size(); i++)
	{
		newRow.push_back(atoi(tokens[i].c_str()));
		if (newRow[i] != PORTAL_MAP_BLANK && newRow[i] != PORTAL_MAP_START)
		{
			float px = i + origin_x;
			float py = portalMap.size() + origin_y;

			gridToreal(px, py);

			portals[newRow[i]]->SetPosition(px, py);
		}
			
	}

	portalMap.push_back(newRow);

}
void CWorldMapScene::Update(DWORD dt) {
	player->Update(dt);
	for (auto& portal : portals)
		portal.second->Update(dt);
	CHUD::GetInstance()->Update();
}
void CWorldMapScene::Render() {
	//render bg
	for (int i = 0; i < background.size(); i++)
		background[i]->Render();

	//render portals
	for (auto& portal : portals)
		portal.second->Render();

	player->Render();
	// render HUD
	CHUD::GetInstance()->Render();
}
void CWorldMapScene::Unload() {
	//clear background
	for (int i = 0; i < background.size(); i++)
		delete	background[i];
	background.clear();

	//clear path
	path.clear();
	//clear portalMap
	portalMap.clear();

	//clear portal
	for (auto& portal : portals)
		delete	portal.second;

	player = NULL;
	//clear assets
	CAnimations::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();



	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CWorldMapScene::ExploreNextMove(float& x, float& y, int direction) {
	//
	int ex, ey;
	ex = x / GRID_SIZE - origin_x;
	ey = y / GRID_SIZE - origin_y;

	float xx, yy;

	switch (direction)
	{
	case EXPLORE_DIRECTION_LEFT:
		while (ex > 0 && path[ey][ex - 1] != PATH_TYPE_BLANK)
		{
			ex--;
			if (path[ey][ex] == PATH_TYPE_STOP)
				break;
		}
		break;
	case EXPLORE_DIRECTION_RIGHT:
		while (ex < col - 1 && path[ey][ex+1] != PATH_TYPE_BLANK)
		{
			ex++;
			if (path[ey][ex] == PATH_TYPE_STOP)
				break;
		}
		break;
	case EXPLORE_DIRECTION_UP:
		while (ey > 0 && path[ey-1][ex] != PATH_TYPE_BLANK)
		{
			ey--;
			if (path[ey][ex] == PATH_TYPE_STOP)
				break;
		}
		break;
	case EXPLORE_DIRECTION_DOWN:
		while (ey < row - 1 && path[ey+1][ex] != PATH_TYPE_BLANK)
		{
			ey++;
			if (path[ey][ex] == PATH_TYPE_STOP)
				break;
		}
		break;
	}

	DebugOut(L"ex:%d, ey:%d\n", ex, ey);

	xx = ex + origin_x;
	yy = ey + origin_y;
	gridToreal(xx, yy);

	x = xx;
	y = yy;
}

int CWorldMapScene::GetPortalIfStandingOn(float x, float y)
{
	int ex, ey;
	ex = x / GRID_SIZE - origin_x;
	ey = y / GRID_SIZE - origin_y;

	// 
	if (portalMap[ey][ex] != PORTAL_MAP_BLANK && portalMap[ey][ex] != PORTAL_MAP_START)
		return portalMap[ey][ex];

	return 0;
}

void CWorldMapScene::SetState(int state) {
	
	switch (state)
	{
	case WORLD_MAP_STATE_IDLE:
	{
		CData* data = CGame::GetInstance()->GetData();
		//if life == 0
		if (data->GetLife() == 0)
		{
			data->ResetData();
		}
		//reset camera
		CGame::GetInstance()->SetCamPos(0, 0);
		//reset timer
		CGame::GetInstance()->GetData()->SetTimer(TIMER_DEFAULT);
		//set player position
		
		if (data->GetCurrentMap() != PORTAL_MAP_START)
		{
			float x, y;
			portals[data->GetCurrentMap()]->GetPosition(x, y);
			player->SetPosition(x, y);
		}
		//update passed portals
		for (int i = 1; i <= data->GetPassedMap(); i++)
			portals[i]->SetState(PORTAL_STATE_CLOSE);
		break;
	}
	case WORLD_MAP_STATE_ENTERING_PORTAL:
	{
		float x, y;
		player->GetPosition(x, y);
		int p = GetPortalIfStandingOn(x, y);

		if (p > 0)
		{
			if (portals[p]->GetState() == PORTAL_STATE_OPEN)
			{
				CData* data = CGame::GetInstance()->GetData();
				data->SetCurrentMap(p);
				CGame::GetInstance()->InitiateSwitchScene(portals[p]->GetSceneId());
				CGame::GetInstance()->SwitchScene();

				return;
			}
		}
		else {
			SetState(WORLD_MAP_STATE_IDLE);
			return;
		}

		break;
	}
	case WORLD_MAP_STATE_RESTART:
		CData* data = CGame::GetInstance()->GetData();
		data->ResetData();
		break;
	}
	this->state = state;
}
