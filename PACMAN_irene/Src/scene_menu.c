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

/* Internal Variables*/
static ALLEGRO_BITMAP* gameTitle = NULL;
static ALLEGRO_BITMAP* map = NULL;
static ALLEGRO_BITMAP* map1 = NULL;
static ALLEGRO_BITMAP* map2 = NULL;
static ALLEGRO_BITMAP* map3 = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
static ALLEGRO_SAMPLE_ID inBGM;
extern int map_i = 1;

// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first. 

//	[HACKATHON 3-1]
//	TODO: Declare variable for button
//	Uncomment and fill the code below
 static Button btnSettings;
 static Button btnArrowleftt;
 static Button btnArrowrightt;

static void init() {


	btnSettings = button_create(730, 20, 50, 50, "Assets/settings.png", "Assets/settings2.png");
	gameTitle = load_bitmap("Assets/title.png");
	map = load_bitmap("Assets/map_nthu.png");
	map1 = load_bitmap("Assets/map_nthu.png");
	map2 = load_bitmap("Assets/map_I2PYANG.png");
	map3 = load_bitmap("Assets/map_mustwin.png");
	btnArrowrightt = button_create(605, 420, 50, 50, "Assets/right.png", "Assets/right.png");
	btnArrowleftt = button_create(125, 420, 50, 50, "Assets/left.png", "Assets/left.png");
	stop_bgm(inBGM);
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic, music_volume);

}




static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {

	btnSettings.hovered = buttonHover(btnSettings, mouse_x, mouse_y);
	btnArrowleftt.hovered = buttonHover(btnArrowleftt, mouse_x, mouse_y);
	btnArrowrightt.hovered = buttonHover(btnArrowrightt, mouse_x, mouse_y);
}

static void on_mouse_down() {
	if (btnSettings.hovered)
		game_change_scene(scene_settings_create());
	if (btnArrowrightt.hovered)
	{
		if (map_i == 1)  map_i = 2;
		else if (map_i == 2)  map_i = 3;
		else if (map_i == 3)  map_i = 1;
	}
	if (btnArrowleftt.hovered)
	{
		if (map_i == 1)  map_i = 3;
		else if (map_i == 2)  map_i = 1;
		else if (map_i == 3)  map_i = 2;

	}
}

static void destroy() {
	stop_bgm(menuBGM);
	al_destroy_bitmap(gameTitle);
	al_destroy_bitmap(map);
	al_destroy_bitmap(map1);
	al_destroy_bitmap(map2);
	al_destroy_bitmap(map3);
	
	al_destroy_bitmap(btnSettings.default_img);
	al_destroy_bitmap(btnSettings.hovered_img);
	al_destroy_bitmap(btnArrowleftt.default_img);
	al_destroy_bitmap(btnArrowleftt.hovered_img);
	al_destroy_bitmap(btnArrowrightt.default_img);
	al_destroy_bitmap(btnArrowrightt.hovered_img);
	
}

static void draw() {

	al_clear_to_color(al_map_rgb(26, 5, 36));

	al_draw_scaled_bitmap(gameTitle, 0, 0, 2500, 1000, 155, 150, 1500, 600, 0);
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 150, ALLEGRO_ALIGN_CENTER, "PRESS \"ENTER\"");

	drawButton(btnSettings);
	drawButton(btnArrowleftt);
	drawButton(btnArrowrightt);

	switch (map_i)
	{
	case 1:
		al_draw_scaled_bitmap(map1, 0, 0, 2500, 1000, 215, 300, 1200, 480, 0);
		break;
	case 2:
		al_draw_scaled_bitmap(map2, 0, 0, 2500, 1000, 215, 300, 1200, 480, 0);
		break;
	case 3:
		al_draw_scaled_bitmap(map3, 0, 0, 2500, 1000, 215, 300, 1200, 480, 0);
		break;
	}
}

static void on_key_down(int keycode) {

	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_main_create());
			break;
		default:
			break;
	}
}

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.

// The only function that is shared across files.
Scene scene_menu_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	game_log("Menu scene created");
	return scene;
}