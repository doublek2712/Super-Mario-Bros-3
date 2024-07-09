#pragma once
#include "Game.h"
#include "Scene.h"

#include "BackgroundElement.h"

class CWorldMapScene : public CScene
{
	vector<LPBGELEMENT> background;

	void _ParseSection_BACKGROUND(string line);
	void _ParseSection_PATH(string line);
	void _ParseSection_PORTAL(string line);
public:
	CWorldMapScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};