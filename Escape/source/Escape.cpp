#include "Escape.hpp"

void instructions(bool rightSide, bool topScreen);

sf2d_texture *img_page3_base = sfil_load_PNG_buffer(page3_base_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3 = sfil_load_PNG_buffer(page3_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3_1 = sfil_load_PNG_buffer(page3_1_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3_2 = sfil_load_PNG_buffer(page3_2_png, SF2D_PLACE_RAM);
sf2d_texture *img_page3_3 = sfil_load_PNG_buffer(page3_3_png, SF2D_PLACE_RAM);
sf2d_texture *img_page5_base = sfil_load_PNG_buffer(page5_base_png, SF2D_PLACE_RAM);
sf2d_texture *img_page5 = sfil_load_PNG_buffer(page5_png, SF2D_PLACE_RAM);
sf2d_texture *img_page5_1 = sfil_load_PNG_buffer(page5_1_png, SF2D_PLACE_RAM);
sf2d_texture *img_page5_2 = sfil_load_PNG_buffer(page5_2_png, SF2D_PLACE_RAM);
sf2d_texture *img_page5_3 = sfil_load_PNG_buffer(page5_3_png, SF2D_PLACE_RAM);
sf2d_texture *img_page8_base = sfil_load_PNG_buffer(page8_base_png, SF2D_PLACE_RAM);
sf2d_texture *img_page8 = sfil_load_PNG_buffer(page8_png, SF2D_PLACE_RAM);
sf2d_texture *img_page8_1 = sfil_load_PNG_buffer(page8_1_png, SF2D_PLACE_RAM);

//init
int debugTF = 1;
char versiontxtt[8] = " Alpha ";
char versiontxtn[9] = "01.00.00";
int vernumqik = 0;

float offset3d = 0.0f, offset3d2 = 0.0f;

int Escape();
int page = 0;
sftd_font *default_fnt, *title_fnt, *story_fnt;
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
	story_fnt = sftd_load_font_mem(BKANT_ttf, BKANT_ttf_size);

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

bool pageIsImage[9] = {
	false, true, false, false, true, false, false, true, false
};

bool movLeft = false;
bool movRight = false;

int Escape()
{
	movLeft = false;
	movRight = false;
	hidScanInput();
	u32 kDown = hidKeysDown();
	if (kDown & KEY_LEFT)
	{
		movLeft = true;
	}
	if (kDown & KEY_RIGHT)
	{
		movRight = true;
	}
	u32 kHeld = hidKeysHeld();
	if (kHeld & KEY_START)
	{
		page = 0;
		return 1;
	}

	if (movLeft)
	{
		if (pageIsImage[page - 2])
			page--;
		page--;
	}
	if (movRight)
	{
		if (pageIsImage[page])
			page++;
		page++;
	}

	sf2d_set_3D(1);
	offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;
	offset3d2 = CONFIG_3D_SLIDERSTATE * 15.0f;

	

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
	sf2d_end_frame();



	sf2d_swapbuffers();
	return 0;
}

void instructions(bool rightSide, bool topScreen)
{
	if (page == 1)
	{
		if (!topScreen)
		{
			sftd_draw_textf_wrap(story_fnt, 10, 10, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     You are one of the leaders of a spy mission operating in the country of Dorado. You have just broken out of a maximum security prison run by the Doradan Secret Police. Your escape has only just begun.");
			sftd_draw_textf_wrap(story_fnt, 10, 60, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     Now you and your group must make it home to safety in Turtalia, which is more than a thousand miles away over semi - desert land and vast mountains.");
			sftd_draw_textf_wrap(story_fnt, 10, 110, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     The year is 2045. A combination of civil wars and foreign attacks has split the United States into three hostile political areas--Dorado, Rebellium, and Turtalia.");
			sftd_draw_textf_wrap(story_fnt, 10, 160, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     Dorado is a repressive police state.It follows only the rule of force, not law, and has designs on the territory of its neighbors.The Doradan Secret Police are feared throughout the continent.");
			sftd_draw_textf_wrap(story_fnt, 10, 210, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     [A] Continue"); // page 3
		}
	}
	if (page == 2)
	{
		sftd_draw_textf(story_fnt, 10, 10, RGBA8(0, 0, 0, 255), 12, "WTF?");
	}
	if (page == 3)
	{
		if (topScreen)
		{
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
		else {
			sftd_draw_textf_wrap(story_fnt, 2, 2, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     The second region, Rebellium, occupies all territory easy of the Mississippi. It is a haphazard collection of minor city-states. They are disorganized and offer no real help in the struggle with Dorado.");
			sftd_draw_textf_wrap(story_fnt, 2, 42, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Turtalia, which you are trying to reach, is made up of the mountain states north of Arizona as well as the northern plains states extending into Canada.");
			sftd_draw_textf_wrap(story_fnt, 2, 82, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     The capital of Turtalia is Denver. Turtalia is a democracy run by elected representatives and governed by a panel of five. It is also your home.");
			sftd_draw_textf_wrap(story_fnt, 2, 122, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Your father is one of the panel of five. He was opposed when you volunteered to go on a spy mission into Dorado, but you went anyway. You were sure that you, and only you, could get the plans for the Doradan invasion of Turtalia--and you did get them.");
			sftd_draw_textf_wrap(story_fnt, 2, 172, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     The Doradan Secret Police arrested you, but fortunately they never suspected that you had learned their invasion plans. Your escape from their prison was due to luck more than to good planning.");
			sftd_draw_textf_wrap(story_fnt, 10, 210, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     [A] Continue"); // page 4
		}
	}
	if (page == 4)
	{
		if (topScreen)
		{
			if (offset3d > 0.0)
			{
				if (rightSide)
				{
					sf2d_draw_texture(img_page5, 0 + (offset3d / 2.0), 0);
					sf2d_draw_texture(img_page5_2, 0 + (offset3d / 4.0), 0);
					sf2d_draw_texture(img_page5_1, 0 + (offset3d / 6.0), 0);
					sf2d_draw_texture(img_page5_3, 0 + (offset3d / 8.0), 0);
				}
				else {
					sf2d_draw_texture(img_page5, 0 - (offset3d / 2.0), 0);
					sf2d_draw_texture(img_page5_2, 0 - (offset3d / 4.0), 0);
					sf2d_draw_texture(img_page5_1, 0 - (offset3d / 6.0), 0);
					sf2d_draw_texture(img_page5_3, 0 - (offset3d / 8.0), 0);
				}
			}
			else {
				sf2d_draw_texture(img_page5_base, 0, 0);
			}
		}
		else {
			sftd_draw_textf_wrap(story_fnt, 2, 2, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Right now you are hiding in a barn on a deserted ranch. You're about seven miles north of what used to be called Gallup, New Mexico. Three other people are with you. The most important--except");
			sftd_draw_textf_wrap(story_fnt, 2, 32, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     for you, of course--is a thirty - year - old woman who is the leader of the resistance in Dorado. Her name is Mimla. There is a large price on her head. She has to get out!");
			sftd_draw_textf_wrap(story_fnt, 2, 72, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     With Mimla is Matt. He's in his early thirties, and it is his responsibility to get her safely out of Dorado.");
			sftd_draw_textf_wrap(story_fnt, 2, 102, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     The third person is a computer specialist named Haven--a silent, nervous man who peers at the world through thick glasses. He is needed in Turtalia to help break Doradn computer codes.");
			sftd_draw_textf_wrap(story_fnt, 2, 142, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Your father, acting through the resistance organization in Dorado, has arranged an escape flight for the four of you. This morning you wait for a Windmaster twin-engine motor-glider to swoop out of the clouds and pick you up.");
			sftd_draw_textf_wrap(story_fnt, 10, 210, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     [A] Continue"); // page 6
		}
	}
	if (page == 6)
	{
		if (!topScreen)
		{
			sftd_draw_textf_wrap(story_fnt, 2, 2, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     You've been waitint for several hours. The plane is no half an hour late. Matt wants to leave.");
			sftd_draw_textf_wrap(story_fnt, 2, 32, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     \"I think we should get out of here and head back to town. I don't want to get caught out here,\" he explains.");
			sftd_draw_textf_wrap(story_fnt, 2, 62, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     You look at the clouds, then at the desert.");
			sftd_draw_textf_wrap(story_fnt, 2, 82, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     \"I don't know,\" you say finally. \"We're in a pretty good spot right here. We can see anyone coming for quite a distance. I know Bill, the pilot, --he's reliable. He'll get here! I think we can wait another half an hour.\"");
			sftd_draw_textf_wrap(story_fnt, 2, 132, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     \"They're closing in on us,\" Matt says tensely. \"I can feel it.\"");
			sftd_draw_textf_wrap(story_fnt, 2, 152, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     There is no sign of the Secret Police on the horizon. But you know they could appear at any moment.");
			sftd_draw_textf_wrap(story_fnt, 2, 210, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     [Y] If you decide to follow Matt's suggestion and return to town."); // page 10
			sftd_draw_textf_wrap(story_fnt, 2, 220, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     [X] If you decide to wait another half hour for the plane."); // page 15
		}
	}
	if (page == 7)
	{
		if (topScreen)
		{
			sftd_draw_textf_wrap(story_fnt, 2, 178, RGBA8(0x00, 0x00, 0x00, 0x0FF), 10, 396, "     You jump to your feet. It's a good thing you can wake up quickly. You and Matt join the others outside. The motor-glider has started its engines for the final approach.");
			sftd_draw_textf_wrap(story_fnt, 2, 208, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 396, "     You admire the slim craft as it swoops down. The Windmaster is a perfect combination: designed in 2012 to be a full-performance glider and power plane, it uses almost no gas once it is airborne. You wouldn't mind having a Windmaster of your own.");
		}
		else {
			
			sftd_draw_textf_wrap(story_fnt, 2, 2, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     The plane is close to the ground, ready to land. You can see Bill at the controls and the Doradan military markings that have been added to the tail as camouflage. Then the plane bobbles, one wing");
			sftd_draw_textf_wrap(story_fnt, 2, 32, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     almost catching the ground. Bill straightens it out and touches down. You wonder what that was--crosswind, maybe?");
			sftd_draw_textf_wrap(story_fnt, 2, 62, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Bill taxis close, swings around to be in position for takeoff, and stops, engines idling. The four of you grab your stuff and run to the door.");
			sftd_draw_textf_wrap(story_fnt, 2, 92, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     You clamber aboard and throw your gear aft. You'll secure it later. You've got to take off quickly in case the plane was spotted.");
			sftd_draw_textf_wrap(story_fnt, 2, 122, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     \"All set, Bill!\" you shout.");
			sftd_draw_textf_wrap(story_fnt, 2, 142, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     There's no answer from the cockipit. You look at Matt questioningly. He shrugs his shoulders. You run into the cockpit. Bill is slumped over the wheel. He's not breakthing!");
			sftd_draw_textf_wrap(story_fnt, 10, 210, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     [A] Continue"); // page 13
		}
	}
	if (page == 9)
	{
		if (topScreen)
		{
			if (offset3d > 0.0)
			{
				if (rightSide)
				{
					sf2d_draw_texture(img_page8, -10 + (offset3d / 2.0), 0);
					sf2d_draw_texture(img_page8_1, -10 + (offset3d / 6.0), 0);
				}
				else {
					sf2d_draw_texture(img_page8, -10 - (offset3d / 2.0), 0);
					sf2d_draw_texture(img_page8_1, -10 - (offset3d / 6.0), 0);
				}
			}
			else {
				sf2d_draw_texture(img_page8_base, 0, 0);
			}
		}
		else {
			sftd_draw_textf_wrap(story_fnt, 2, 2, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     \"Welcome aboard, copilot,\" you say to Matt.");
			sftd_draw_textf_wrap(story_fnt, 2, 12, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Grinning ear to ear, Matt saultes you. \"At your service, pilot,\" he answers.");
			sftd_draw_textf_wrap(story_fnt, 2, 32, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     While you buckle into the pilot's seat, Matt goes aft to make sure that Mimla and Haven are all set for takeoff. They have made a makeshift bed for Bill and are trying to keep him comfortable. When Matt");
			sftd_draw_textf_wrap(story_fnt, 2, 62, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     returns, you quickly run through the instruments and switches with him: altimeter, variometer, fuel gauges, tachometers, engine temperature, throttle controls, engine heater switches, and so on.");
			sftd_draw_textf_wrap(story_fnt, 2, 92, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Everything is ready. You roll the plane to the end of the strip. Your heart pounds in your chest, but otherwise you feel calm and capable.");
			sftd_draw_textf_wrap(story_fnt, 2, 112, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     Once more you scan the control panel. Then you adjust the throttles. The plane begins rolling down the sandy desert. At the right moment you pull the control column back and you're airborne. You did it!");
			sftd_draw_textf_wrap(story_fnt, 2, 152, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     The altimeter spins rapidly as your Windmaster climbs out and heads toward the Sangre de Cristo Mountains. You pass through 15,000 feet, then 16,000. Finally you top out at 17,000 feet. All");
			sftd_draw_textf_wrap(story_fnt, 2, 182, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 316, "     around you are towering cumulus clouds bulging with moisture. You know that some of them hide violent turbulence that could easily rip the wings from the plane.");
			sftd_draw_textf_wrap(story_fnt, 10, 220, RGBA8(0x00, 0x00, 0x00, 0xFF), 10, 300, "     [A] Continue"); // page 17
		}
	}
}
