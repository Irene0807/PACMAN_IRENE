#include "scene_settings.h"
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

static Button btnCheckws;
static Button btnCheckupdown;
static Button btnVolumeup;
static Button btnVolumedown;
static Button btnArrowleft;
static Button btnArrowright;
static Button btnEffectup;
static Button btnEffectdown;
static Button btnBack;

static ALLEGRO_BITMAP* set_title = NULL;
static ALLEGRO_BITMAP* checkbox = NULL;
static ALLEGRO_BITMAP* ws = NULL;
static ALLEGRO_BITMAP* updown = NULL;
static ALLEGRO_BITMAP* soft = NULL;
static ALLEGRO_BITMAP* joyful = NULL;
static ALLEGRO_BITMAP* sound = NULL;

static ALLEGRO_SAMPLE_ID settingBGM;
static ALLEGRO_SAMPLE_ID effectBGM;

static int music_i = 1;
static int check_x = 130;
extern int flag;

static void musicbar();
static void audiobar();
// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static void init() {
	set_title = load_bitmap("Assets/set_title.png");
	checkbox = load_bitmap("Assets/checkbox2.png");
	ws = load_bitmap("Assets/WS.png");
	updown = load_bitmap("Assets/updown.png");
	soft = load_bitmap("Assets/soft.png");
	joyful = load_bitmap("Assets/joyful.png");
	sound = load_bitmap("Assets/sound.png");
	btnCheckws = button_create(130, 190, 50, 50, "Assets/checkbox.png", "Assets/checkbox2.png");
	btnCheckupdown = button_create(420, 190, 50, 50, "Assets/checkbox.png", "Assets/checkbox2.png");
	btnVolumeup = button_create(640, 420, 50, 50, "Assets/plus.png", "Assets/plus.png");
	btnVolumedown = button_create(240, 420, 50, 50, "Assets/minus.png", "Assets/minus.png");
	btnArrowright = button_create(635, 290, 50, 50, "Assets/right.png", "Assets/right.png");
	btnArrowleft = button_create(265, 290, 50, 50, "Assets/left.png", "Assets/left.png");
	btnEffectup = button_create(640, 560, 50, 50, "Assets/plus.png", "Assets/plus.png");
	btnEffectdown = button_create(240, 560, 50, 50, "Assets/minus.png", "Assets/minus.png");
	btnBack = button_create(280, 630, 220, 115, "Assets/back.png", "Assets/back2.png");
	stop_bgm(settingBGM);
	settingBGM = play_bgm(themeMusic, music_volume);
}




static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {

	btnCheckws.hovered = buttonHover(btnCheckws, mouse_x, mouse_y);
	btnCheckupdown.hovered = buttonHover(btnCheckupdown, mouse_x, mouse_y);
	btnVolumeup.hovered = buttonHover(btnVolumeup, mouse_x, mouse_y);
	btnVolumedown.hovered = buttonHover(btnVolumedown, mouse_x, mouse_y);
	btnArrowleft.hovered = buttonHover(btnArrowleft, mouse_x, mouse_y);
	btnArrowright.hovered = buttonHover(btnArrowright, mouse_x, mouse_y);
	btnEffectup.hovered = buttonHover(btnEffectup, mouse_x, mouse_y);
	btnEffectdown.hovered = buttonHover(btnEffectdown, mouse_x, mouse_y);
	btnBack.hovered = buttonHover(btnBack, mouse_x, mouse_y);
}

static void on_mouse_down() {
	if (btnCheckws.hovered)
	{
		if (flag == 1)
		{
			flag = 0;
			check_x = 130;
			game_log("%d", flag);
		}
	}
	if (btnCheckupdown.hovered)
	{
		if (flag == 0)
		{
			flag = 1;
			check_x = 420;
			game_log("%d", flag);
		}
	}

	if (btnVolumeup.hovered)
	{
		if (music_volume < 1)
		{
			music_volume += 0.1;
			stop_bgm(settingBGM);
			settingBGM = play_bgm(themeMusic, music_volume);
			game_log("%f", music_volume);
		}
	}
	if (btnVolumedown.hovered)
	{
		if (music_volume > 0)
		{
			music_volume -= 0.1;
			stop_bgm(settingBGM);
			settingBGM = play_bgm(themeMusic, music_volume);
			game_log("%f", music_volume);
		}
	}
	if (btnArrowright.hovered)
	{
		if (music_i == 1)
		{
			inMusic = inMusic2;
			stop_bgm(settingBGM);
			settingBGM = play_bgm(inMusic2, music_volume);
			music_i = 2;
		}
		else if (music_i == 2)
		{
			inMusic = inMusic1;
			stop_bgm(settingBGM);
			settingBGM = play_bgm(inMusic1, music_volume);
			music_i = 1;
		}
	}
	if (btnArrowleft.hovered)
	{
		if (music_i == 1)
		{
			themeMusic = inMusic2;
			stop_bgm(settingBGM);
			settingBGM = play_bgm(inMusic2, music_volume);
			music_i = 2;
		}
		else if (music_i == 2)
		{
			themeMusic = inMusic1;
			stop_bgm(settingBGM);
			settingBGM = play_bgm(inMusic1, music_volume);
			music_i = 1;
		}
	}
	if (btnEffectup.hovered)
	{
		if (effect_volume < 1)
		{
			effect_volume += 0.1;
			stop_bgm(effectBGM);
			stop_bgm(settingBGM);
			effectBGM = play_audio(PACMAN_MOVESOUND, effect_volume);
			game_log("%f", effect_volume);
		}
	}
	if (btnEffectdown.hovered)
	{
		if (effect_volume > 0)
		{
			effect_volume -= 0.1;
			stop_bgm(effectBGM);
			stop_bgm(settingBGM);
			effectBGM = play_audio(PACMAN_MOVESOUND, effect_volume);
			game_log("%f", effect_volume);
		}
	}
	if (btnBack.hovered)
	{
		game_change_scene(scene_menu_create());
	}

}

static void destroy() {
	stop_bgm(settingBGM);
	stop_bgm(effectBGM);

	al_destroy_bitmap(btnCheckws.default_img);
	al_destroy_bitmap(btnCheckws.hovered_img);
	al_destroy_bitmap(btnCheckupdown.default_img);
	al_destroy_bitmap(btnCheckupdown.hovered_img);
	al_destroy_bitmap(btnVolumeup.default_img);
	al_destroy_bitmap(btnVolumeup.hovered_img);
	al_destroy_bitmap(btnVolumedown.default_img);
	al_destroy_bitmap(btnVolumedown.hovered_img);
	al_destroy_bitmap(btnArrowright.default_img);
	al_destroy_bitmap(btnArrowright.hovered_img);
	al_destroy_bitmap(btnArrowleft.default_img);
	al_destroy_bitmap(btnArrowleft.hovered_img);
	al_destroy_bitmap(btnEffectup.default_img);
	al_destroy_bitmap(btnEffectup.hovered_img);
	al_destroy_bitmap(btnEffectdown.default_img);
	al_destroy_bitmap(btnEffectdown.hovered_img);
	al_destroy_bitmap(btnBack.default_img);
	al_destroy_bitmap(btnBack.hovered_img);
	al_destroy_bitmap(set_title);
	al_destroy_bitmap(ws);
	al_destroy_bitmap(updown);
	al_destroy_bitmap(soft);
	al_destroy_bitmap(joyful);
	al_destroy_bitmap(sound);

}
// The only function that is shared across files.

static void draw(void) {
	al_clear_to_color(al_map_rgb(26, 5, 36));

	drawButton(btnCheckws);
	drawButton(btnCheckupdown);
	drawButton(btnVolumeup);
	drawButton(btnVolumedown);
	drawButton(btnArrowleft);
	drawButton(btnArrowright);
	drawButton(btnEffectup);
	drawButton(btnEffectdown);
	drawButton(btnBack);
	musicbar();
	audiobar();


	al_draw_scaled_bitmap(set_title, 0, 0, 2500, 1000, 270, 55, 750, 290, 0);
	al_draw_scaled_bitmap(checkbox, 0, 0, 2500, 1000, check_x, 190, 480, 190, 0);
	al_draw_scaled_bitmap(ws, 0, 0, 2500, 1000, 190, 200, 417, 167, 0);
	al_draw_scaled_bitmap(updown, 0, 0, 2500, 1000, 490, 190, 417, 167, 0);
	al_draw_scaled_bitmap(sound, 0, 0, 2500, 1000, 130, 420, 417, 167, 0);
	al_draw_scaled_bitmap(sound, 0, 0, 2500, 1000, 130, 560, 417, 167, 0);
	al_draw_filled_rectangle(290, 135, 510, 140, al_map_rgb(255, 255, 255));
	al_draw_text(menuFont, al_map_rgb(177, 153, 180), 130, 305, 0, "BGM : ");
	al_draw_text(menuFont, al_map_rgb(177, 153, 180), 425, 390, 0, "BGM");
	al_draw_text(menuFont, al_map_rgb(177, 153, 180), 415, 530, 0, "AUDIO");

	switch (music_i)
	{
	case 1:
		al_draw_scaled_bitmap(joyful, 0, 0, 2500, 1000, 365, 260, 833, 333, 0);
		break;

	case 2:
		al_draw_scaled_bitmap(soft, 0, 0, 2500, 1000, 365, 260, 833, 333, 0);
		break;

	}
}

Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	scene.musicbar = &musicbar;
	scene.audiobar = &audiobar;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

static void musicbar()
{
	for (float i = 0.05; i <= 1.05; i += 0.1)
	{
		if (i <= music_volume)
			al_draw_filled_rounded_rectangle(295 + i * 300, 430, 325 + i* 300, 465, 0, 0, al_map_rgb(177, 153, 180));
		else
			al_draw_filled_rounded_rectangle(295 + i * 300, 430, 325 + i * 300, 465, 0, 0, al_map_rgb(111, 70, 116));
	}
}

static void audiobar()
{
	for (float i = 0.05; i <= 1.05; i += 0.1)
	{
		if (i <= effect_volume)
			al_draw_filled_rounded_rectangle(295 + i * 300, 570, 325 + i * 300, 595, 0, 0, al_map_rgb(177, 153, 180));
		else
			al_draw_filled_rounded_rectangle(295 + i * 300, 570, 325 + i * 300, 595, 0, 0, al_map_rgb(111, 70, 116));
	}
}