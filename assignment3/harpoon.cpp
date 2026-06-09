#include "harpoon.h"
#include <cmath>
#include <allegro5/allegro.h>

harpoon::harpoon(bool isCannon) {
    x = 400;
    y = 550;
    cannonX = 400;
    cannonY = 550;
    speed = 10;
    rotationSpeed = 3;
    isFired = false;
    angle = 0;
    firedAngle = 0;

    harpoon_sprite = al_load_bitmap("harpoon.png");
    if (!harpoon_sprite) harpoon_sprite = al_create_bitmap(10, 10);

    if (isCannon) {
        cannon_sprite = al_load_bitmap("cannon.png");
        if (!cannon_sprite) cannon_sprite = al_create_bitmap(10, 10);
    }
    else {
        cannon_sprite = nullptr;
    }
}

harpoon::~harpoon() {
    if (harpoon_sprite) al_destroy_bitmap(harpoon_sprite);
	if (cannon_sprite) al_destroy_bitmap(cannon_sprite);
}

void harpoon::DrawHarpoon() {
	// i use rotated bitmaps here to make sure the cannon and harpoon rotate together, and the harpoon rotates in the direction of the cannon when fired.
    if (cannon_sprite) {
        al_draw_rotated_bitmap(cannon_sprite,
            al_get_bitmap_width(cannon_sprite) / 2,
            al_get_bitmap_height(cannon_sprite),
            cannonX, cannonY,
            angle * (3.14159f / 180.0f),
            0);
    }

    if (isFired && harpoon_sprite) {
        al_draw_rotated_bitmap(harpoon_sprite,
            al_get_bitmap_width(harpoon_sprite) / 2,   //center x pivot
            al_get_bitmap_height(harpoon_sprite) / 2,  //center y pivot
            x, y,
            firedAngle * (3.14159f / 180.0f),          // same angle as cannon
            0);
    }
}

void harpoon::FireHarpoon(float a, int cx, int cy) {
    if (isFired) return;

    float pi = 3.14159f;
    float radian = (a - 90.0f) * (pi / 180.0f);
    int cannonLength = 128; //matches the height of the cannon sprite

    x = cx + static_cast<int>(cannonLength * cos(radian));
    y = cy + static_cast<int>(cannonLength * sin(radian));

    firedAngle = a;
    isFired = true;
}

void harpoon::CollideHarpoon(fish f[], int cSize) {
    if (!isFired) return;

    // check off screen
    if (x < 0 || x > 800 || y < 0 || y > 600) {
        isFired = false;
        return;
    }

    // check against each fish
    for (int i = 0; i < cSize; i++) {
        if (!f[i].getLive()) continue;

        bool hitX = x > f[i].getX() && x < f[i].getX() + f[i].getBoundX();
        bool hitY = y > f[i].getY() && y < f[i].getY() + f[i].getBoundY();

        if (hitX && hitY) {
            isFired = false;
            f[i].setLive(false);
        }
    }
}

void harpoon::RotateCannon(bool left) {
    //simply rotates the cannon, and also clamps the anlges at 75 degrees each way
	if (left) {
		angle -= rotationSpeed;
	}
	else {
		angle += rotationSpeed;
	}

	if (angle < -75) {
		angle = -75;
	}
	else if (angle > 75) {
		angle = 75;
	}
}

void harpoon::UpdateHarpoon() {
	if (!isFired) return;

	float pi = 3.14159f;
	float radian = (firedAngle + 90.0f) * (pi / 180.0f);

	x -= static_cast<int>(speed * cos(radian));
	y -= static_cast<int>(speed * sin(radian));

	if (x < 0 || x > 800 || y < 0 || y > 600) {
		isFired = false;
	}
}
