#pragma once
#include <allegro5/allegro.h>
#include "fish.h"

class harpoon
{
public:
	harpoon(bool isCannon = false);
	~harpoon();
	void DrawHarpoon();
	void FireHarpoon(float a, int cx, int cy);
	void UpdateHarpoon();
	void CollideHarpoon(fish f[], int cSize);
	void RotateCannon(bool left);
	int getAngle() { return angle; }
	bool getIsFired() { return isFired; }
	int getCannonX() { return cannonX; }
	int getCannonY() { return cannonY; }
	
private:
	int x;
	int y;
	int cannonX;
	int cannonY;
	int speed;
	int rotationSpeed;
	bool isFired;
	float angle;
	float firedAngle;
	ALLEGRO_BITMAP* harpoon_sprite;
	ALLEGRO_BITMAP* cannon_sprite;
};

