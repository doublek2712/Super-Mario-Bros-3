#include "WorldMapScene.h"
#include "WorldMapKeyHandler.h"

#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Configs.h"
#include "debug.h"
#include "HUD.h"
#include "AssetLoader.h"

#define WSCENE_SECTION_UNKNOWN -1
#define WSCENE_SECTION_ASSETS	1
#define WSCENE_SECTION_BACKGROUND	2
#define WSCENE_SECTION_PORTALS	3
#define WSCENE_SECTION_PATH	4

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

CWorldMapScene::CWorldMapScene(int id, LPCWSTR filePath) :
	CScene(id, filePath) {
	key_handler = new CWorldMapKeyHandler(this);
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
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
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
void CWorldMapScene::_ParseSection_PATH(string line) {

}
void CWorldMapScene::_ParseSection_PORTAL(string line) {

}
void CWorldMapScene::Update(DWORD dt) {

}
void CWorldMapScene::Render() {
	for (int i = 0; i < background.size(); i++)
		background[i]->Render();
	// render HUD
	CHUD::GetInstance()->Render();
}
void CWorldMapScene::Unload() {
	//clear assets
	CAnimations::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();



	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}