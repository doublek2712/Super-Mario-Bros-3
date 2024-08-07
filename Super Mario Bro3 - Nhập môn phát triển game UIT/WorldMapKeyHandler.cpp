#include "WorldMapKeyHandler.h"
#include "WorldMapScene.h"
#include "MarioOnWorldMap.h"


void CWorldMapKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CWorldMapScene* scene = (CWorldMapScene*)CGame::GetInstance()->GetCurrentScene();
	CMarioOnWorldMap* mario = scene->GetPlayer();
	float x, y;
	mario->GetPosition(x, y);

	switch (KeyCode)
	{
	case DIK_UP:
		scene->ExploreNextMove(x, y, EXPLORE_DIRECTION_UP);
		mario->GoTo(x, y);
		break;
	case DIK_DOWN:
		scene->ExploreNextMove(x, y, EXPLORE_DIRECTION_DOWN);
		mario->GoTo(x, y);
		break;
	case DIK_LEFT:
		scene->ExploreNextMove(x, y, EXPLORE_DIRECTION_LEFT);
		mario->GoTo(x, y);
		break;
	case DIK_RIGHT:
		scene->ExploreNextMove(x, y, EXPLORE_DIRECTION_RIGHT);
		mario->GoTo(x, y);
		break;

	case DIK_S:
		scene->SetState(WORLD_MAP_STATE_ENTERING_PORTAL);
		break;
	}

}

void CWorldMapKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	
}

void CWorldMapKeyHandler::KeyState(BYTE* states)
{
	
}