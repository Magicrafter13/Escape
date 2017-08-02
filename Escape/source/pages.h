#pragma once
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include "Title_Image_png.h"
#include "page3_png.h"
#include "page3_base_png.h"
#include "page3_1_png.h"
#include "page3_2_png.h"
#include "page3_3_png.h"
//#include "page5_png.h"

const sf2d_texture *img_pages[5][4] = {
	{sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM)},
	{sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM)},
	{sfil_load_PNG_buffer(page3_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(page3_1_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(page3_2_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(page3_3_png, SF2D_PLACE_RAM)},
	{sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM)},
	{sfil_load_PNG_buffer(page3_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(page3_1_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(page3_2_png, SF2D_PLACE_RAM), sfil_load_PNG_buffer(page3_3_png, SF2D_PLACE_RAM)}
};

int page_extras[5] = {
	0,
	3,
	0,
	0,
	3
};

int page_exits[5][3] = {
	{1, 3, 0},
	{0, 0, 0},
	{1, 4, 0},
	{1, 6, 0},
	{0, 0, 0}
};

int page_compliment[5] = {
	0,
	0,
	2,
	5,
	0
};

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)

float offset3d = 0.0F;

void draw_page_extras(int page_to_draw, int image_to_draw, bool rightSide, bool topScreen)
{
	offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;
	if (rightSide)
		sf2d_draw_texture(img_pages[page_to_draw][image_to_draw], 0 + (offset3d / (2.0 * image_to_draw)), 0);
	else
		sf2d_draw_texture(img_pages[page_to_draw][image_to_draw], 0 - (offset3d / (2.0 * image_to_draw)), 0);
}
