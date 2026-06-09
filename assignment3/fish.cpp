#include "fish.h"
#include <allegro5/allegro.h>

fish::fish() {
    x = 0;
    y = 0;
    boundx = 50; 
    boundy = 50; 
    speed = 1;
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

    if (y > 500) {
        fishHit = true;
        live = false;
    }
}