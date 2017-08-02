#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>
using std::string;
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <sftd.h>
#include <vector>
#include "Title_Image_png.h"
#include "plane_png.h"
#include "plane_mask_png.h"
#include "calibri_ttf.h"
#include "BOOKOS_ttf.h"
#include "sprite.h"
#include "pages.h"

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)

extern PrintConsole bottomScreen, versionWin, killBox;

extern char versiontxtt[8];
extern char versiontxtn[9];
extern int vernumqik;
int credits();
extern int debugTF;
const char * keyBoard(char * hintTxt, int maxNumbers, bool multiLine);

#define ANSI "\x1b["
#define RED "31"
#define B_RED "41"
#define GREEN "32"
#define B_GREEN "42"
#define YELLOW "33"
#define B_YELLOW "43"
#define BLUE "34"
#define B_BLUE "44"
#define MAGENTA "35"
#define B_MAGENTA "45"
#define CYAN "36"
#define B_CYAN "46"
#define WHITE "37"
#define B_WHITE "47"
#define BRIGHT "2"
#define CRESET "\x1b[0m"
#define PRESET "\x1b[0;0H"
#define ASEP ";"
#define CEND "m"
#define PEND "H"