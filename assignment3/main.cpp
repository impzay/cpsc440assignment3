#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "harpoon.h"
#include "fish.h"


const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int FPS = 60;
const int MAX_FISH = 5;
const int MAX_HARPOON = 5;
int total_fish_hit = 0;
ALLEGRO_COLOR sand_color = al_map_rgb(194, 178, 128);

bool keys[5] = { false };
const int LEFT = 0;
const int RIGHT = 1;
const int SPACE = 2;



int main() {
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(disp, "Harpoon Shooter!");

	ALLEGRO_BITMAP* background = al_load_bitmap("background.png");
    ALLEGRO_FONT* font = al_create_builtin_font();

    harpoon cannon(true);
    harpoon harpoons[MAX_HARPOON];
    fish fishes[MAX_FISH];

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    bool running = true;
    bool redraw = false;

    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            bool left;

			for (int i = 0; i < MAX_FISH; i++) {
                if (fishes[i].fishHit) {
					total_fish_hit ++;
                    fishes[i].fishHit = false;
					
                }
			}
            if (total_fish_hit >= 5) {
                al_draw_bitmap(background, 0, 0, 0);
              
                al_draw_text(font, al_map_rgb(0,0,0), SCREEN_W / 2, SCREEN_H / 2 - 24, ALLEGRO_ALIGN_CENTRE, "You lose.");
                al_flip_display();
                al_rest(3.0); // wait for 3 seconds
                //end game
                running = false;
            }

            if (keys[LEFT]) {
                left = true;
                cannon.RotateCannon(left);
            }
            if (keys[RIGHT]) {
                left = false;
                cannon.RotateCannon(left);
            }

			for (int i = 1; i < MAX_HARPOON; i++) {
				harpoons[i].UpdateHarpoon();
			}

           //i have for loops for spawning the fish and call the update and collide functions for the fish and harpoons.
           //I put them in the timer block so that they get updated every frame.
			for (int i = 1; i < MAX_FISH; i++) {
				if (!fishes[i].getLive()) {
					fishes[i].StartFish(SCREEN_W, SCREEN_H);
					break;
				}
                fishes[i].UpdateFish();
				fishes[i].CollideFish();
                harpoons[i].CollideHarpoon(fishes, MAX_FISH);
			}


            /*
            fish::StartFish();
            fish::UpdateFish();
            harpoon::CollideHarpoon();
            fish::CollideFish();
            */
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                running = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
				//this for loops will check how many harpoons are fired, and fire the ones that are not fired.
                // this way i can have multiple harpoons on the screen at once.
                for (int i = 1; i < MAX_HARPOON; i++) {
                    if (!harpoons[i].getIsFired()) {
                        harpoons[i].FireHarpoon(cannon.getAngle(), cannon.getCannonX(), cannon.getCannonY());
						//i get the angle and pos from the cannon so i can keep it consistent with the cannon rotation and pos.
                        break;
                    }
                }
                break;
            }
        }
        if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            }
        }
        //draw block
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_draw_bitmap(background, 0, 0, 0);
			al_draw_filled_rectangle(0, 600 - 100, 800, 600, sand_color); //draw sand


            cannon.DrawHarpoon(); //draws cannon
			for (int i = 1; i < MAX_HARPOON; i++) {
				harpoons[i].DrawHarpoon(); //all harpoon projecticles
			}
            for (int i = 0; i < MAX_FISH; i++) {
                fishes[i].DrawFish(); //all fishs
            }

            al_flip_display();
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}