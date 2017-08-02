#include "Escape.hpp"

void instructions(bool rightSide, bool topScreen);

sf2d_texture *img_page3_base = sfil_load_PNG_buffer(page3_base_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3 = sfil_load_PNG_buffer(page3_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3_1 = sfil_load_PNG_buffer(page3_1_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3_2 = sfil_load_PNG_buffer(page3_2_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3_3 = sfil_load_PNG_buffer(page3_3_png, SF2D_PLACE_RAM);

//init
int debugTF = 1;
char versiontxtt[8] = " Alpha ";
char versiontxtn[9] = "01.00.00";
int vernumqik = 0;

float offset3d = 0.0f, offset3d2 = 0.0f;

int Escape();
int page = 0;
sftd_font *default_fnt, *title_fnt;
const char *test = "Test!";
const char *test3d = "Test 3D!!!";

bool touchInBox(touchPosition touch, int x, int y, int w, int h)
{
	int tx=touch.px;
	int ty=touch.py;
	u32 kDown = hidKeysDown();
	if (kDown & KEY_TOUCH && tx > x && tx < x+w && ty > y && ty < y+h) {
		return true;
	} else {
		return false;
	}
}

touchPosition touch;
bool gameRunning = true;

FS_Archive sdmcArchive;

void openSD()
{
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
}

void closeSD()
{
	FSUSER_CloseArchive(sdmcArchive);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	sf2d_init();
	sftd_init();
	sf2d_set_3D(1);

	hidTouchRead(&touch);

	sf2d_set_clear_color(RGBA8(0x95, 0x95, 0x95, 0xFF));
	sf2d_set_vblank_wait(1);
	sf2d_texture *img_title = sfil_load_PNG_buffer(Title_Image_png, SF2D_PLACE_RAM);
	sf2d_texture *img_plane = sfil_load_PNG_buffer(plane_png, SF2D_PLACE_RAM);
	sf2d_texture *img_plane_mask = sfil_load_PNG_buffer(plane_mask_png, SF2D_PLACE_RAM);

	default_fnt = sftd_load_font_mem(calibri_ttf, calibri_ttf_size);
	title_fnt = sftd_load_font_mem(BOOKOS_ttf, BOOKOS_ttf_size);

	// Main loop
	while (aptMainLoop())
	{
		hidTouchRead(&touch);
		page = 3;
		if (touchInBox(touch, 0, 0, 320, 240)) {
			while (page != 0)
				if (Escape() == 1)
					break;
		}
		hidScanInput();
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) break; // break in order to return to hbmenu

		offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(img_title, -10 - (offset3d / 4.0), -20);
		if (abs(offset3d) > 0.0)
		{
			sf2d_draw_texture(img_plane_mask, -10 - (offset3d / 3.0), -20);
			sf2d_draw_texture(img_plane, -10 - (offset3d / 6.0), -20);
		}
		for (int a = 0; a < 3; a++)
			for (int b = 0; b < 3; b++)
				sftd_draw_textf(default_fnt, 139 + b - (offset3d / 8.0), 19 + a, RGBA8(0x00, 0x00, 0x00, 0xFF), 40, "ESCAPE");
		sftd_draw_textf(default_fnt, 140 - (offset3d / 8.0), 20, RGBA8(0xFA, 0x24, 0xFF, 0xFF), 40, "ESCAPE");
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_TOP, GFX_RIGHT);
		sf2d_draw_texture(img_title, -10 + (offset3d / 4.0), -20);
		if (abs(offset3d) > 0.0)
		{
			sf2d_draw_texture(img_plane_mask, -10 + (offset3d / 3.0), -20);
			sf2d_draw_texture(img_plane, -10 + (offset3d / 6.0), -20);
		}
		for (int a = 0; a < 3; a++)
			for (int b = 0; b < 3; b++)
				sftd_draw_textf(default_fnt, 139 + b + (offset3d / 8.0), 19 + a, RGBA8(0x00, 0x00, 0x00, 0xFF), 40, "ESCAPE");
		sftd_draw_textf(default_fnt, 140 + (offset3d / 8.0), 20, RGBA8(0xFA, 0x24, 0xFF, 0xFF), 40, "ESCAPE");
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	// Exit services
	sf2d_fini();
	sftd_fini();
	sf2d_free_texture(img_title);
	
	return 0;
}

int Escape()
{
	hidScanInput();
	u32 kHeld = hidKeysHeld();
	if (kHeld & KEY_START)
		return 1;
	
	sf2d_set_3D(1);
	offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;
	offset3d2 = CONFIG_3D_SLIDERSTATE * 15.0f;
	int offset3d_i = offset3d, offset3d2_i = offset3d2;

	

	sf2d_start_frame(GFX_TOP, GFX_LEFT);
	//sftd_draw_textf(default_fnt, 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF), 32, "%d\n%d", offset3d_i, offset3d2_i);
	instructions(false, true);
	sf2d_end_frame();



	sf2d_start_frame(GFX_TOP, GFX_RIGHT);
	//sftd_draw_textf(default_fnt, 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF), 32, "%d\n%d", offset3d_i, offset3d2_i);
	instructions(true, true);
	sf2d_end_frame();



	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
	instructions(false, false);
	sf2d_swapbuffers();
	return 0;
}

void instructions(bool rightSide, bool topScreen)
{
	if (page == 3)
	{
		if (topScreen)
			if (offset3d > 0.0)
			{
				if (rightSide)
				{
					sf2d_draw_texture(img_page3, 0 + (offset3d / 2.0), 0);
					sf2d_draw_texture(img_page3_1, 0 + (offset3d / 4.0), 0);
					sf2d_draw_texture(img_page3_2, 0 + (offset3d / 6.0), 0);
					sf2d_draw_texture(img_page3_3, 0 + (offset3d / 8.0), 0);
				}
				else {
					sf2d_draw_texture(img_page3, 0 - (offset3d / 2.0), 0);
					sf2d_draw_texture(img_page3_1, 0 - (offset3d / 4.0), 0);
					sf2d_draw_texture(img_page3_2, 0 - (offset3d / 6.0), 0);
					sf2d_draw_texture(img_page3_3, 0 - (offset3d / 8.0), 0);
				}
			}
			else
				sf2d_draw_texture(img_page3_base, 0, 0);
	}
	if (page_compliment[page] != 0)
	{
		if (topScreen)
		{
			for (int i = 0; i < page_extras[page_compliment[page]]; i++)
				draw_page_extras(page_compliment[page], i, rightSide, topScreen);
		}
	}
}
