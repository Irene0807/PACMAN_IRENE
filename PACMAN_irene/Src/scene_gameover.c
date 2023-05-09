#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_gameover.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"


// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.


/* Define your static vars / function prototypes below. */

static ALLEGRO_BITMAP* gameover_logo = NULL;
static ALLEGRO_BITMAP* leaf1 = NULL;
static ALLEGRO_BITMAP* leaf2 = NULL;
static Button btnRestart;
static Button btnBackMenu;
extern ALLEGRO_TIMER* game_tick_timer;
char prscore[3000];
extern int game_main_Score;
extern int flag;
extern FILE *fp = NULL;
errno_t err;
char buff[1005][1005];
char tmpscore[1005][10];
char tmptime[1005][10];

static void init() {

	gameover_logo = load_bitmap("Assets/gameover_logo.png");
	leaf1 = load_bitmap("Assets/leaf1.png");
	leaf2 = load_bitmap("Assets/leaf2.png");
	btnRestart = button_create(120, 510, 240, 140, "Assets/restart.png", "Assets/restart2.png");
	btnBackMenu = button_create(430, 510, 240, 140, "Assets/backmenu.png", "Assets/backmenu2.png");
	int i = 1;
	int inflag = 0;
	if ((err = fopen_s(&fp, "Assets/record.txt", "r")) != 0)
		printf("The file 'record.txt','r' was not opened\n");
	else {
		printf("The file 'record.txt','r' was opened\n");

		while (!feof(fp)) {
			fgets(buff[i], 100, fp);
			for (int j = 0; j < 4; j++)  tmpscore[i][j] = buff[i][j];
			for (int j = 5; j < 10; j++) tmptime[i][j - 5] = buff[i][j];
			i++;
		}
		for (int j = 1; j < i - 1; j++) {
			printf("*%d %d\n", atoi(tmpscore[j]), atoi(tmptime[j]));
		}

		fclose(fp);
	}

	if ((err = fopen_s(&fp, "Assets/record.txt", "w")) != 0)
		printf("The file 'record.txt','w' was not opened\n");
	else {
		printf("The file 'record.txt','w' was opened\n");
		if (i > 4) {
			for (int j = 1; j < i - 1; j++) {
				if (game_main_Score > atoi(tmpscore[j])) {
					for (int k = 1; k < i - 1; k++) {
						if(k != j)  fprintf(fp, "%4d %4d\n", atoi(tmpscore[k]), atoi(tmptime[k]));
					}
					fprintf(fp, "%4d %4d\n", game_main_Score, al_get_timer_count(game_tick_timer) / 100);
					printf("a\n");
					inflag = 1;
					break;
				}
				else if (game_main_Score == atoi(tmpscore[j])) {
					if (al_get_timer_count(game_tick_timer) / 100 > atoi(tmptime[j])) {
						for (int k = 1; k < i - 1; k++) {
							if (k != j)  fprintf(fp, "%4d %4d\n", atoi(tmpscore[k]), atoi(tmptime[k]));
						}
						fprintf(fp, "%4d %4d\n", game_main_Score, al_get_timer_count(game_tick_timer) / 100);
						printf("b\n");
						inflag = 1;
						break;
					}
				}
			}
			if (inflag == 0) {
				for (int k = 1; k < i - 1; k++) {
					fprintf(fp, "%4d %4d\n", atoi(tmpscore[k]), atoi(tmptime[k]));
				}
			}
		}
		else {
			for (int k = 1; k < i - 1; k++) {
				fprintf(fp, "%4d %4d\n", atoi(tmpscore[k]), atoi(tmptime[k]));
			}
			fprintf(fp, "%4d %4d\n", game_main_Score, al_get_timer_count(game_tick_timer) / 100);
		}
		
		fclose(fp);

	}

}


static void draw(void ){

	al_clear_to_color(al_map_rgb(26, 5, 36));
	
	drawButton(btnRestart);
	drawButton(btnBackMenu);
	snprintf(prscore, 1000, "YOUR SCORE:  %d", game_main_Score);
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 250, 445, 0, prscore);

	al_draw_scaled_bitmap(gameover_logo, 0, 0, 2500, 1000,  8, 60, 1000, 400,  0);
	al_draw_scaled_bitmap(leaf1, 0, 0, 2500, 1000, 615, 650, 1700, 700, 0);
	al_draw_scaled_bitmap(leaf2, 0, 0, 2500, 1000, 8, 650, 1700, 700, 0);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {

	btnRestart.hovered = buttonHover(btnRestart, mouse_x, mouse_y);
	btnBackMenu.hovered = buttonHover(btnBackMenu, mouse_x, mouse_y);

}

static void on_mouse_down() {

	if (btnRestart.hovered)
	{
		game_change_scene(scene_main_create());
	}
	if (btnBackMenu.hovered)
	{
		game_change_scene(scene_menu_create());
	}
}

static void on_key_down(int keycode) {

	if (flag == 1) {
		switch (keycode) {
		case ALLEGRO_KEY_RIGHT:
			game_change_scene(scene_menu_create());
			break;
		case ALLEGRO_KEY_LEFT:
			game_change_scene(scene_main_create());
			break;
		default:
			break;
		}
	}
	else if (flag == 0) {
		switch (keycode) {
		case ALLEGRO_KEY_D:
			al_draw_filled_rectangle(290, 135, 510, 140, al_map_rgb(255, 255, 255));
			game_change_scene(scene_menu_create());
			break;
		case ALLEGRO_KEY_A:
			al_draw_filled_rectangle(290, 135, 510, 140, al_map_rgb(255, 255, 255));
			game_change_scene(scene_main_create());
			break;
		default:
			break;
		}
	}

}

static void destroy() {

	al_destroy_bitmap(btnRestart.default_img);
	al_destroy_bitmap(btnRestart.hovered_img);
	al_destroy_bitmap(btnBackMenu.default_img);
	al_destroy_bitmap(btnBackMenu.hovered_img);
	al_destroy_bitmap(gameover_logo);
}

// The only function that is shared across files.
Scene scene_gameover_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Gameover";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_key_down = &on_key_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Gameover scene created");
	return scene;
}