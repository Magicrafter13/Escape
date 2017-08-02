#include "sprite.h"
void sprite::draw(int relative_x, int relative_y)
{
	int step = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sf2d_draw_rectangle(x + relative_x + (Scale * j), y + relative_y + (Scale * i), Scale, Scale, RGBA8(R[step], G[step], B[step], A[step]));
			step++;
		}
	}
	/*if (width == 14)
	{
		std::cout << "\x1b[5;0H";
		for (int i = 0; i < 4; i++)
			std::cout << "                                        ";
		std::cout << "\x1b[5;0H";
		std::cout << "Pixel 1: X: " << x + 0 << " Y: " << y + 0 << " RGB: " << colorDataR[0] << " " << colorDataG[0] << " " << colorDataB[0] << " A: " << colorDataA[0] << "\n";
		std::cout << "Pixel 2: X: " << x + 1 << " Y: " << y + 1 << " RGB: " << colorDataR[1] << " " << colorDataG[1] << " " << colorDataB[1] << " A: " << colorDataA[1] << "\n";
		std::cout << "Pixel 3: X: " << x + 0 << " Y: " << y + 0 << " RGB: " << colorDataR[2] << " " << colorDataG[2] << " " << colorDataB[2] << " A: " << colorDataA[2] << "\n";
		std::cout << "Pixel 4: X: " << x + 1 << " Y: " << y + 1 << " RGB: " << colorDataR[3] << " " << colorDataG[3] << " " << colorDataB[3] << " A: " << colorDataA[3] << "\n";
	}*/
}

obj_Enemy::obj_Enemy(std::string type) {
	if (type == "GENO")
		isGeno = true;
	if (type == "goblin")
		isGoblin = true;
}
