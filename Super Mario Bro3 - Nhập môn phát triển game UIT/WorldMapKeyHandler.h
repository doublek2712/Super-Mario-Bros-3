#pragma once
#include "Scene.h"

class CWorldMapKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorldMapKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};