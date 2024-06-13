#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Configs.h"
#include "debug.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Ground.h"
#include "Block.h"
#include "BackgroundElement.h"
#include "Mario.h"
#include "SuperLeaf.h"
#include "SuperMushroom.h"
#include "Pipe.h"
#include "Wood.h"
#include "VenusPiranha.h"
#include "Koopa.h"

#include "SampleKeyEventHandler.h"

#define BG_ELEMENT_WIDTH 16
#define BG_ELEMENT_HEIGHT 16

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	isCamYPosAdjust = FALSE;
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_BACKGROUND	3
#define SCENE_SECTION_BOUNDARIES	4

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_BACKGROUND(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int x = atoi(tokens[0].c_str());
	int y = atoi(tokens[1].c_str());
	int row = atoi(tokens[2].c_str());
	int col = atoi(tokens[3].c_str());
	int spriteID = atoi(tokens[4].c_str());

	LPBGELEMENT element = new CBackgroundElement(x, y, row, col, spriteID);
	
	this->background.push_back(element);
}

void CPlayScene::_ParseSection_BOUNDARIES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // skip invalid lines

	b_left = atoi(tokens[0].c_str());
	b_top = atoi(tokens[1].c_str());
	b_right = atoi(tokens[2].c_str());
	b_bottom = atoi(tokens[3].c_str());


}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;


	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_BLOCK:
	{	
		gridToreal(x, y);
		int type = atoi(tokens[3].c_str());
		CGameObject* tmp = NULL;
		switch (type) {
		case CONTAIN_COIN:
			tmp = new CBouncingCoin(x, y - GRID_SIZE);
			break;
		case CONTAIN_SUPER_LEAF:
			CSuperMushroom* tmp2 = new CSuperMushroom(x, y );
			objects.push_back(tmp2);
			tmp = new CSuperLeaf(x, y - GRID_SIZE, tmp2);
			tmp2 = NULL;
			delete tmp2;
			break;
		}
		
		objects.push_back(tmp);
		obj = new CBlock(x, y, type, tmp);
		tmp = NULL;
		delete tmp;
		break;
	}
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;

	case OBJECT_TYPE_PLATFORM:
	{
		gridToreal(x, y);

		int length = atoi(tokens[3].c_str());
		int sprite_begin = atoi(tokens[4].c_str());
		int sprite_middle = atoi(tokens[5].c_str());
		int sprite_end = atoi(tokens[6].c_str());

		obj = new CPlatform(
			x, y,
			length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_GROUND:
	{
		gridToreal(x, y);
		int length = atoi(tokens[3].c_str());
		int sprite_begin = atoi(tokens[4].c_str());
		int sprite_middle = atoi(tokens[5].c_str());
		int sprite_end = atoi(tokens[6].c_str());

		obj = new CGround(
			x, y,
			length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		gridToreal(x, y);
		int dir = atoi(tokens[3].c_str());
		int flip = atoi(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());

		obj = new CPipe(x, y, dir, flip, length);
		break;
	}

	//case OBJECT_TYPE_PORTAL:
	//{
	//	float r = (float)atof(tokens[3].c_str());
	//	float b = (float)atof(tokens[4].c_str());
	//	int scene_id = atoi(tokens[5].c_str());
	//	obj = new CPortal(x, y, r, b, scene_id);
	//	break;
	//}
	case OBJECT_TYPE_WOOD:
	{
		gridToreal(x, y);
		obj = new CWood(x, y);
		break;
	}
	case OBJECT_TYPE_VENUS:
	{
		gridToreal(x, y);

		int height = atoi(tokens[3].c_str());
		x += 8; 
		y += (height > 1)? 8 : 4;
		
		obj = new CVenusPiranha(x, y, height);
		break;
	}
	case OBJECT_TYPE_KOOPA:
	{
		BOOLEAN isBlock = (atoi(tokens[3].c_str()) == 0) ? FALSE : TRUE;
		obj = new CKoopa(x, y, isBlock);
		
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	objects.push_back(obj);

	obj = NULL;
	delete obj;
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; }; 
		if (line == "[BACKGROUND]") { section = SCENE_SECTION_BACKGROUND; continue; };
		if (line == "[BOUNDARIES]") { section = SCENE_SECTION_BOUNDARIES; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
		case SCENE_SECTION_BOUNDARIES: _ParseSection_BOUNDARIES(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{


	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
		if(objects[i] != player)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	if (cx <= b_left*GRID_SIZE) {
		player->SetPosition(b_left * GRID_SIZE, cy);
		player->SetState(MARIO_STATE_IDLE);
	}
	if (cx >= b_right * GRID_SIZE) {
		player->SetPosition(b_right * GRID_SIZE, cy);
		player->SetState(MARIO_STATE_IDLE);
	}

	CGame* game = CGame::GetInstance();	
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	float s_width, s_height;
	game->GetScreenSize(s_width, s_height);

	if (cx < b_left * GRID_SIZE) cx = b_left * GRID_SIZE;
	if (cx > b_right * GRID_SIZE - s_width)
		cx = b_right * GRID_SIZE - s_width;

	if (cy < b_top * GRID_SIZE)
		cy = b_top * GRID_SIZE;

	CMario* mario = dynamic_cast<CMario*>(player);
	if (!mario->IsFlying())
	{
		if (!isCamYPosAdjust)
		{
			if (cy > b_bottom * GRID_SIZE - s_height - s_height / 2 - GRID_SIZE * 2)
				cy = b_bottom * GRID_SIZE - s_height;
		}
		else
		{
			if (cy > b_bottom * GRID_SIZE - s_height)
			{
				cy = b_bottom * GRID_SIZE - s_height;
				isCamYPosAdjust = FALSE;
			}
		}
	}
	else 
	{
		if (cy > b_bottom * GRID_SIZE - s_height)
			cy = b_bottom * GRID_SIZE - s_height;
		else {
			isCamYPosAdjust = TRUE;
		}
	}
	//if (cy > b_bottom * GRID_SIZE - s_height)
	//	cy = b_bottom * GRID_SIZE - s_height;
	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	// render background
	for (int i = 0; i < background.size(); i++)
		background[i]->Render();
	// render obj
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

*/
void CPlayScene::Unload()
{
	//clear objects
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	//clear background
	for (int i = 0; i < background.size(); i++)
		delete	background[i];
	background.clear();

	player = NULL;

	//clear assets
	CAnimations::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();

	

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			//DebugOut(L"Obj was deleted\n");
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CPlayScene::SpawnObject(LPGAMEOBJECT obj) 
{
	objects.push_back(obj);
}