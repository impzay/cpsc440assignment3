#include "fish.h"
#include <allegro5/allegro.h>

fish::fish() {
    x = 0;
    y = 0;
    speed = 1;
    boundx = 50;
    boundy = 50;
    sprite = al_load_bitmap("fish.png");
    live = false;
}

fish::~fish() {
    if (sprite) al_destroy_bitmap(sprite);
}

void fish::DrawFish() {
    if (!live) return;
    al_draw_bitmap(sprite, x, y, 0);
}

void fish::StartFish(int WIDTH, int HEIGHT) {
    if (live) return;

    // randomize starting x, start at top
    x = rand() % WIDTH;
    y = 0;
    live = true;
}

void fish::UpdateFish() {
    if (!live) return;
    y += speed;
}

void fish::CollideFish() {
    if (!live) return;

    int stageH = 50;
    int stageW = 800;

    // hit the stage at bottom of screen
    bool hitX = x > 0 && x < stageW;
    bool hitY = y + boundy >= 600 - stageH;

    if (hitY && hitX) {
        live = false;
    }

    if (y > 600) {
        live = false;
    }
}