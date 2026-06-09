#pragma once
#include <allegro5/bitmap.h>


class fish
{
public:
	fish();
	~fish();
	void DrawFish();
	void StartFish(int WIDTH, int HEIGHT);
	void UpdateFish();
	void CollideFish();
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
	int fishHit = false;
private:
	int x;
	int y;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* sprite;
	bool live;

};

