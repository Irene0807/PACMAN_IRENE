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
//static ALLEGRO_SAMPLE_ID menuBGM;
static Button btnRestart;
static Button btnBackMenu;
char prscore[3000];
extern int game_main_Score;

static void init() {

	gameover_logo = load_bitmap("Assets/gameover_logo.png");
	leaf1 = load_bitmap("Assets/leaf1.png");
	leaf2 = load_bitmap("Assets/leaf2.png");
	btnRestart = button_create(120, 510, 240, 140, "Assets/restart.png", "Assets/restart2.png");
	btnBackMenu = button_create(430, 510, 240, 140, "Assets/backmenu.png", "Assets/backmenu2.png");

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
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Gameover scene created");
	return scene;
}