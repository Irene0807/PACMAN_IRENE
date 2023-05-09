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
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.


/* Define your static vars / function prototypes below. */

static ALLEGRO_BITMAP* win_logo = NULL;
static ALLEGRO_BITMAP* win_pic = NULL;
static ALLEGRO_BITMAP* award1 = NULL;
static ALLEGRO_BITMAP* award2 = NULL;
//static ALLEGRO_SAMPLE_ID menuBGM;
static Button btnRestart;
static Button btnBackMenu;
char prscore[3000];
extern int game_main_Score;
extern flag;

static void init() {

	win_logo = load_bitmap("Assets/win_logo.png");
	win_pic = load_bitmap("Assets/win_pic.png");
	award1 = load_bitmap("Assets/award.png");
	award2 = load_bitmap("Assets/award.png");
	btnRestart = button_create(100, 500, 240, 140, "Assets/restart.png", "Assets/restart2.png");
	btnBackMenu = button_create(450, 500, 240, 140, "Assets/backmenu.png", "Assets/backmenu2.png");

}


static void draw(void ){

	al_clear_to_color(al_map_rgb(26, 5, 36));
	
	drawButton(btnRestart);
	drawButton(btnBackMenu);

	al_draw_scaled_bitmap(win_logo, 0, 0, 2500, 1000, 150, 220, 2000, 800,  0);
	al_draw_scaled_bitmap(win_pic, 0, 0, 2500, 1000, 325, 70, 1250, 500, 0);
	snprintf(prscore, 1000, "YOUR SCORE:  %d", game_main_Score);
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 250, 440, 0, prscore);
	al_draw_scaled_bitmap(award1, 0, 0, 2500, 1000, 40, 700, 1000, 400, 0);
	al_draw_scaled_bitmap(award2, 0, 0, 2500, 1000, 650, 700, 1000, 400, 0);

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
			game_change_scene(scene_menu_create());
			break;
		case ALLEGRO_KEY_A:
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
	al_destroy_bitmap(win_logo);
	al_destroy_bitmap(win_pic);
	al_destroy_bitmap(award1);
	al_destroy_bitmap(award2);
}

// The only function that is shared across files.
Scene scene_win_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Win";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_key_down = &on_key_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Win scene created");
	return scene;
}