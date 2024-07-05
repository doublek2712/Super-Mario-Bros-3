#pragma once
#include "GameObject.h"
#include "debug.h"

#define OBJ_GRAVITY 0.002f

class CPlatformChecker : public CGameObject
{
	BOOLEAN isOnPlatform;
	int height, width;
	float ax, ay;
	
	
public:
	CPlatformChecker(float x, float y, int height, int width) :CGameObject(x, y) {
		
		this->height = height;
		this->width = width;
		this->ax = 0;
		this->ay = OBJ_GRAVITY;
		this->vx = 0;
		this->vy = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - width / 2;
		top = y - height / 2;
		right = left + width;
		bottom = top + height;

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		vx += ax * dt;
		vy += ay * dt;

		isOnPlatform = false;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void Render()
	{
		RenderBoundingBox();
	}
	void OnNoCollision(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
	}
	void OnCollisionWith(LPCOLLISIONEVENT e)
	{
		if (!e->obj->IsBlocking()) {
			return;
		}

		if (e->ny != 0)
		{
			vy = 0;
			if (e->ny < 0) {
				isOnPlatform = true;
			}
			
		}


	}
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }

	BOOLEAN IsFallOffPlatform() {
		return !isOnPlatform;
	}
	void SetVx(float vx) {
		this->vx = vx; 
	}
};